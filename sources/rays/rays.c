#include "rays.h"

# include "mlx.h"
# include "x_mini_struct.h"
# include "x_linear_algebra.h"
# include <math.h>

double    is_intersect_plane(t_ray *ray, t_plane *plane, double *t);
double    is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder, double *t2);

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

static void	new_ray(t_cam *cam, t_ray *ray, int x, int y)
{
	double		norm_scale_x;
	double		norm_scale_y;

	cast_vector_mat_ray(&cam->origin_vect, &ray->origin_vect);
	norm_scale_y = normalize_pixel(cam->resol[1], y, 0) * cam->scale;
	norm_scale_x = normalize_pixel(cam->resol[0], x, 1) * cam->scale
		* cam->aspect;
	scale_and_add_vectors(cam, ray, norm_scale_x, norm_scale_y);
	normalize_vector(ray->dir_vect.axis);
}

void	put_pxl(t_mlx *mlx, int x, int y, unsigned int color)
{	
	int		pxl_pos;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{	
		pxl_pos = x *  mlx->img.bpp / 8 + y * mlx->img.line_len;
		*(unsigned int *)(mlx->img.img_data + pxl_pos) = color;
	}
}

double	is_intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_ray_vector	sphere_ray_vect;
	double			a;
	double			b;
	double			c;	
	double			discrim;

	subtract_vector(ray->origin_vect.axis, sphere->origin_vect.axis,
		sphere_ray_vect.axis);
	a = scalar_product(ray->dir_vect.axis, ray->dir_vect.axis);
	b = 2 * scalar_product(sphere_ray_vect.axis, ray->dir_vect.axis);
	c = scalar_product(sphere_ray_vect.axis, sphere_ray_vect.axis)
		- sphere->square_radius;
	discrim = b * b - 4 * a * c;
	if (discrim < 0)
	    return (0.0);
	return ((-b - sqrt(discrim)) / (2 * a));
}

int	get_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char[])
		{r, g, b});
}

int	get_background_color(t_ray *ray)
{
	double a;

	a = 0.5 * (ray->dir_vect.axis[1] + 10.0);
    return (1.0 - a) * get_color(255, 255, 255) + a * get_color(0.5 * 255, 0.7 * 255, 1.0 * 255);
}

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector scaled_vect;	

	scale_vector(ray->dir_vect.axis, t, scaled_vect.axis);
	add_vector(ray->origin_vect.axis, scaled_vect.axis, inter_pt->axis);	
}

int		is_behind_cam(double t)
{
	return (t <= 0.0);
}
// void	get_normal_color(t_ray *ray, double t, t_sphere *sphere, t_color *color)
// {
// 	t_ray_vector inter_pt;
// 	t_ray_vector normal;
	
// 	get_intersect_point(ray, t, &inter_pt);
// 	subtract_vector(inter_pt.axis, sphere->origin_vect.axis, normal.axis);
// 	normalize_vector(normal.axis);
// 	cast_vector_to_color(&normal, color);
// }

// void	get_sphere_normal_spotlight_color(t_ray *ray, double t, t_sphere *sphere, t_spotlight *spotlight, t_color *color)
// {
// 	t_ray_vector	inter_pt;
// 	t_ray_vector	normal;
// 	t_ray_vector	light_ray;
// 	t_ray_vector	scaled_vect;
// 	double 			light_coef;

// 	get_intersect_point(ray, t, &inter_pt);
// 	subtract_vector(&inter_pt, &sphere->origin_vect, &normal);
// 	normalize_vector(&normal);
// 	// subtract_vector(&inter_pt, &spotlight->origin_vect, &light_ray);
// 	subtract_torvec(&spotlight->origin_vect, &inter_pt, &light_ray);
// 	normalize_vector(&light_ray);
// 	light_coef = scalar_product(&light_ray,&normal);
// 	light_coef = normalize_zero_one(light_coef);
// 	scale_color(&sphere->color, light_coef, &scaled_vect);
// 	cast_vector_ray_to_color(&scaled_vect, color);
// }

// void	color_with_ambiant_light(t_color *mesh_color, t_ambiant_light *ambiant_light, t_color *new_color)
// {
// 	t_color			subt_color;
// 	t_color			ambiant_scaled_color;

// 	subtract_color_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255}, mesh_color, &subt_color);
// 	scale_color_color(&ambiant_light->color, ambiant_light->intensity, &ambiant_scaled_color);
// 	double tmp = ambiant_scaled_color.rgb[0] / 255.0;
// 	new_color->rgb[0] = tmp * subt_color.rgb[0] + mesh_color->rgb[0];	
// 	double tmp2 = ambiant_scaled_color.rgb[1] / 255.0;
// 	new_color->rgb[1] = tmp2 * subt_color.rgb[1] + mesh_color->rgb[1];
// 	double tmp3 = ambiant_scaled_color.rgb[2] / 255.0;
// 	new_color->rgb[2] = tmp3 * subt_color.rgb[2] + mesh_color->rgb[2];
// }

void	color_with_ambiant_light(t_color *mesh_color, t_ambiant_light *ambiant_light, t_color *new_color)
{
	t_color	subt_color;
	t_color	ambiant_scaled_color;
	double	tmp_color;

	scale_color(&ambiant_light->color, ambiant_light->intensity, &ambiant_scaled_color);
	tmp_color = ambiant_scaled_color.rgb[0] / 255.0;
	new_color->rgb[0] = tmp_color * mesh_color->rgb[0];	
	tmp_color = ambiant_scaled_color.rgb[1] / 255.0;
	new_color->rgb[1] = tmp_color * mesh_color->rgb[1];
	tmp_color = ambiant_scaled_color.rgb[2] / 255.0;
	new_color->rgb[2] = tmp_color * mesh_color->rgb[2];
}

void	get_sphere_normal_spotlight_color(t_ray *ray, double t, t_sphere *sphere, t_spotlight *spotlight, t_color *color, t_ambiant_light *ambiant_light)
{
	t_ray_vector	inter_pt;
	t_ray_vector	normal;
	t_ray_vector	light_ray;
	t_ray_vector	scaled_vect;
	double 			light_coef;
	t_color			subt_color;
	t_color			ambiant_color;

	get_intersect_point(ray, t, &inter_pt);
	subtract_vector(inter_pt.axis, sphere->origin_vect.axis, normal.axis);
	normalize_vector(normal.axis);
	// subtract_vector(&inter_pt, &spotlight->origin_vect, &light_ray);
	subtract_vector(spotlight->origin_vect.axis, inter_pt.axis, light_ray.axis);
	normalize_vector(light_ray.axis);
	light_coef = scalar_product(light_ray.axis ,normal.axis);
	light_coef = normalize_zero_one(light_coef);
	color_with_ambiant_light(&sphere->color, ambiant_light, &ambiant_color);
	subtract_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255}, &ambiant_color, &subt_color);
	
	scale_color(&subt_color, light_coef * spotlight->intensity, color);
	//cast_vector_ray_to_color(&scaled_vect, color);
	add_color(color, &ambiant_color, color);
	// scale_color(&sphere->color, light_coef, &scaled_vect);
	// cast_vector_ray_to_color(&scaled_vect, color);
}

void	get_plane_normal_spotlight_color(t_ray *ray, double t, t_plane *plane, t_spotlight *spotlight, t_color *color, t_sphere *sphere, t_ambiant_light *ambiant_light)
{	
	t_ray_vector	normal;
	t_ray			light_ray;
	t_ray_vector	scaled_vect;
	double 			light_coef;
	t_color			subt_color;
	t_color			ambiant_color;

	cast_vector_mat_ray(&plane->norm_vect, &normal);
	get_intersect_point(ray, t, &light_ray.origin_vect);
		// subtract_vector(&inter_pt, &plane->origin_vect, &normal);
	//normalize_vector(&normal);
	subtract_vector(spotlight->origin_vect.axis, light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	normalize_vector(light_ray.dir_vect.axis);
	color_with_ambiant_light(&plane->color, ambiant_light, &ambiant_color);
	//printf("ambiant color :%i, %i, %i\n", ambiant_color.rgb[0], ambiant_color.rgb[1], ambiant_color.rgb[2]);
	if (is_intersect_sphere(&light_ray, sphere))
	{		
		//*color = (t_color){.rgb[0] = 0, .rgb[1] = 0, .rgb[2] = 0};
		*color = ambiant_color;		
		return ;
	}
	light_coef = scalar_product(normal.axis, light_ray.dir_vect.axis);
	//light_coef = normalize_zero_one(light_coef);
	
	subtract_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255}, &ambiant_color, &subt_color);

	scale_color(&subt_color, light_coef * spotlight->intensity, color);
	//cast_vector_ray_to_color(&scaled_vect, color);
	add_color(color, &ambiant_color, color);
}

void	launch_rays(t_mlx *mlx, t_data *data)
{
	t_ray			ray;
	double			x;
	double			y;
	double			t;
	t_ray_vector	*subt_vect;
	t_color 		color;
	t_ray_vector	p;
	double			t2;
	double			t3;
	double			inter_bulb;

	t2 = 0;
	t3 = 0;
	y = -1;
	while (++y < data->cam.resol[1])
	{
		x = -1;
		while (++x < data->cam.resol[0])
		{
			new_ray(&data->cam, &ray, x, y);
			t = is_intersect_sphere(&ray, &data->spheres[0]);
			inter_bulb = is_intersect_sphere(&ray, &data->spotlight.bulb);
			t2 = is_intersect_plane(&ray, &data->planes[0], NULL);
			t3 = is_intersect_cylinder(&ray, &data->cylinders[0], NULL);
			// printf("t2: %f\n", t2);

			if (t && !is_behind_cam(t))
			{
				get_sphere_normal_spotlight_color(&ray, t, &data->spheres[0], &data->spotlight, &color,  &data->ambiant_light);
				put_pxl(mlx, x, y, get_color(color.rgb[0], color.rgb[1], color.rgb[2]));
			}
			else if (t3 && !is_behind_cam(t3))
			{
				put_pxl(mlx, x, y, get_color(0,255,255));
			}
			else if (inter_bulb && !is_behind_cam(inter_bulb))
				put_pxl(mlx, x, y, get_color(data->spotlight.bulb.color.rgb[0], data->spotlight.bulb.color.rgb[1], data->spotlight.bulb.color.rgb[2]));
			else if (t2 && !is_behind_cam(t2))
			{
				get_plane_normal_spotlight_color(&ray, t2, &data->planes[0], &data->spotlight, &color, &data->spheres[0], &data->ambiant_light);
				put_pxl(mlx, x, y, get_color(color.rgb[0], color.rgb[1], color.rgb[2]));
			}
			else
				put_pxl(mlx, x, y, get_background_color(&ray));	
		}		
	}
}
