#include "rays.h"

# include "mlx.h"
# include "x_mini_struct.h"
# include "x_linear_algebra.h"
# include <math.h>

double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
double	is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder,
			t_ray_vector *i);
double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y);
void	invert_vector(double a[], double b[], double r_a[], double r_b[]);

static void	scale_and_add_vectors(t_cam *cam, t_ray *ray, double norm_scale_x,
	double norm_scale_y)
{
	t_matrix_vector	scaled_up;
	t_matrix_vector	scaled_right;
	t_matrix_vector	scaled_forward;
	t_matrix_vector	sum_vect;

	scale_vector(cam->up_vect.axis, norm_scale_y, scaled_up.axis);
	scale_vector(cam->right_vect.axis, norm_scale_x, scaled_right.axis);
	scale_vector(cam->forward_vect.axis, cam->focal_len, scaled_forward.axis);
	add_vector(scaled_up.axis, scaled_right.axis, sum_vect.axis);
	add_vector(sum_vect.axis, scaled_forward.axis, ray->dir_vect.axis);
}

static double	normalize_pixel(int screen_size, int pixel, int x_flag)
{
	if (!screen_size)
		return (0.0);
	if (x_flag)
		return (((pixel + 0.5) / screen_size) * 2 - 1);
	return ((1 - 2 * (pixel + 0.5) / screen_size));
}

void	new_ray(t_cam *cam, t_ray *ray, int x, int y)
{
	double	norm_scale_x;
	double	norm_scale_y;

	cast_vector_mat_ray(&cam->origin_vect, &ray->origin_vect);
	norm_scale_y = normalize_pixel(cam->resol[1], y, 0) * cam->scale;
	norm_scale_x = normalize_pixel(cam->resol[0], x, 1) * cam->scale
		* cam->aspect;
	scale_and_add_vectors(cam, ray, norm_scale_x, norm_scale_y);
	normalize_vector(ray->dir_vect.axis);
}

void	put_pxl(t_mlx *mlx, int x, int y, unsigned int color)
{
	const double	inverse_eight = 0.125;
	int				pxl_pos;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl_pos = x * mlx->img.bpp * inverse_eight + y * mlx->img.line_len;
		*(unsigned int *)(mlx->img.img_data + pxl_pos) = color;
	}
}

int	get_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char []){r, g, b, 0});
}

int	get_background_color(t_ray *ray)
{
	double	a;

	a = 0.5 * (ray->dir_vect.axis[1] + 10.0);
	return ((1.0 - a) * get_color(255, 255, 255)
		+ a * get_color(0.5 * 255, 0.7 * 255, 1.0 * 255));
}

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector	scaled_vect;

	scale_vector(ray->dir_vect.axis, t, scaled_vect.axis);
	add_vector(ray->origin_vect.axis, scaled_vect.axis, inter_pt->axis);
}

int	is_behind_cam(double t)
{
	return (t <= 0.0);
}

void	color_with_ambiant_light(t_color *mesh_color,
	t_ambiant_light *ambiant_light, t_color *new_color)
{
	t_color	ambiant_scaled_color;
	double	tmp_color;
	int		i;

	scale_color(&ambiant_light->color, ambiant_light->intensity,
		&ambiant_scaled_color);
	i = -1;
	while (++i < AXIS)
	{
		tmp_color = ambiant_scaled_color.rgb[i] / 255.0;
		new_color->rgb[i] = tmp_color * mesh_color->rgb[i];
	}
}

void	get_local_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector	scaled_vect;

	scale_vector(ray->dir_vect.axis, t, inter_pt->axis);
}

int	has_sphere_shadow(t_data *data, void *mesh, t_ray *light_ray)
{
	int				i;
	double			t;
	long double		mesh_mag;
	long double		light_mag;
	t_ray_vector	intersect_pt;

	i = -1;
	while (++i < data->sp_nbr)
	{
		if (mesh && (void *) &data->spheres[i] != mesh)
		{
			t = is_intersect_sphere(light_ray, &data->spheres[i], NULL);
			if (t)
			{
				get_local_intersect_point(light_ray, t, &intersect_pt);
				light_mag = get_vector_magnitude(light_ray->dir_vect.axis);
				mesh_mag = get_vector_magnitude(intersect_pt.axis);
				if (mesh_mag - 1e-5 < light_mag)
					return (1);
			}
		}
	}
	return (0);
}

int	has_cylinder_shadow(t_data *data, void *mesh, t_ray *light_ray)
{
	int				i;
	double			t;
	long double		mesh_mag;
	long double		light_mag;
	t_ray_vector	intersect_pt;

	i = -1;
	while (++i < data->cy_nbr)
	{
		if (mesh && (void *) &data->cylinders[i] != mesh)
		{
			t = is_intersect_cylinder(light_ray, &data->cylinders[i], NULL);
			if (t)
			{
				get_local_intersect_point(light_ray, t, &intersect_pt);
				light_mag = get_vector_magnitude(light_ray->dir_vect.axis);
				mesh_mag = get_vector_magnitude(intersect_pt.axis);
				if (mesh_mag - 1e-5 < light_mag)
					return (1);
			}
		}
	}
	return (0);
}

int	has_shadow(t_data *data, void *mesh, t_ray *light_ray)
{
	if (has_sphere_shadow(data, mesh, light_ray))
		return (1);
	if (has_cylinder_shadow(data, mesh, light_ray))
		return (1);
	return (0);
}

double	calculate_light_attenuation(t_ray *light_ray, double intensity)
{
	double			light_mag;
	const double	kc = 1.0;
	const double	kl = 45e-4;
	const double	kq = 75e-50;

	light_mag = get_vector_magnitude(light_ray->dir_vect.axis);
	return (intensity / (kc + kl * light_mag + kq * light_mag * light_mag));
}

void	add_self_shadowing(double light_coef, double light_attenuation,
	t_color *color)
{
	t_color	color_sav;

	color_sav = *color;
	if (light_coef < 0.5)
	{
		scale_color(color, 0.15 * light_attenuation, color);
		subtract_color(&color_sav, color, color);
	}
}

void	add_initial_shading( t_ray *ray, t_ray_vector *normal,
	t_color *ambiantly_color, t_color *color)
{
	double	light_coef;

	light_coef = scalar_product(ray->dir_vect.axis, normal->axis);
	normalize_zero_one(&light_coef);
	scale_color(ambiantly_color, light_coef, color);
	subtract_color(ambiantly_color, color, ambiantly_color);
}

void	add_shading(t_add_shading_params *params)
{
	t_color	subt_color;
	t_ray	light_ray_sav;

	light_ray_sav = *params->light_ray;
	normalize_vector(params->light_ray->dir_vect.axis);
	*params->light_coef = scalar_product(params->light_ray->dir_vect.axis,
			params->normal->axis);
	normalize_zero_one(params->light_coef);
	subtract_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255},
		params->ambiently_color, &subt_color);
	*params->light_attenuat = calculate_light_attenuation(&light_ray_sav,
			*params->light_coef * params->spotlight->intensity);
	scale_color(&subt_color, *params->light_attenuat, params->color);
	add_color(params->color, params->ambiently_color, params->color);
}

int	get_sphere_color(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;
	double			light_attenuat;
	double			light_coef;	

	get_intersect_point(params->ray, params->t, &light_ray.origin_vect);
	subtract_vector(light_ray.origin_vect.axis,
		((t_sphere *) params->mesh)->origin_vect.axis, normal.axis);
	normalize_vector(normal.axis);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	color_with_ambiant_light(&((t_sphere *) params->mesh)->color,
		&params->data->ambiant_light, &ambiantly_color);
	if (((t_sphere *) params->mesh)->which_t == 2)
		symmetrize_vector(normal.axis);
	add_initial_shading(params->ray, &normal, &ambiantly_color, params->color);
	if (has_shadow(params->data, (t_sphere *) params->mesh, &light_ray))
		return (*params->color = ambiantly_color, 0);
	add_shading(&(t_add_shading_params){&light_ray, &normal,
		&params->data->spotlight, &ambiantly_color, params->color,
		&light_attenuat, &light_coef});
	add_self_shadowing(light_coef, light_attenuat, params->color);
	return (0);
} 

void	get_plane_color(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;

	cast_vector_mat_ray(&((t_plane *) params->mesh)->norm_vect, &normal);
	get_intersect_point(params->ray, params->t, &light_ray.origin_vect);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	color_with_ambiant_light(&((t_plane *) params->mesh)->color,
		&params->data->ambiant_light, &ambiantly_color);
	if (has_shadow(params->data, params->mesh, &light_ray))
	{
		*params->color = ambiantly_color;
		return ;
	}
	add_shading(&(t_add_shading_params){&light_ray, &normal,
		&params->data->spotlight, &ambiantly_color, params->color,
		&(double){0.0}, &(double){0.0}});
}

void	launch_rays(t_mlx *mlx, t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->cam.resol[1])
	{
		x = -1;
		while (++x < data->cam.resol[0])
			exec_launch_rays(mlx, data, x, y);
	}
}
