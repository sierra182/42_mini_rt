#include "rays.h"

# include "mlx.h"
# include "x_mini_struct.h"
# include "x_linear_algebra.h"
# include <math.h>

void	display_error(char *str);

double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
double	is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder,
			t_ray_vector *i);
double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y);
void	invert_vector(double a[], double b[], double r_a[], double r_b[]);
int		has_shadow(t_data *data, void *mesh, t_ray *light_ray);
int		is_equal_vector(double a[], double b[]);
int		is_sphere_surface_between(t_sphere *sphere, t_spotlight *spotlight);

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

double	normalize_pixel(int screen_size, int pixel, int x_flag)
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
	return (*(int *)(unsigned char []){b, g, r, 0});
}

/**========================================================================
 *                           get_background_color
 *========================================================================**/
int	get_background_color(t_ray *ray, t_data *data)
{
	int		color[2];
	int		rgb[3];
	double	dir;
	t_color *bg_color;
	double intensity;

	intensity = data->ambiant_light.intensity;
	bg_color = (t_color *)&data->ambiant_light.color;
	dir = (ray->dir_vect.axis[1] + 1.0) * 0.5;
	color[0] = get_color(intensity * 255, intensity * 255, intensity * 255);
	color[1] = get_color(bg_color->rgb[0] * intensity, bg_color->rgb[1] * intensity, bg_color->rgb[2] * intensity);
	rgb[0] = (int)((1.0 - dir) * ((color[1] >> 16) & 0xFF) + dir * ((color[0] >> 16) & 0xFF));
	rgb[1] = (int)((1.0 - dir) * ((color[1] >> 8) & 0xFF) + dir * ((color[0] >> 8) & 0xFF));
	rgb[2] = (int)((1.0 - dir) * (color[1] & 0xFF) + dir * (color[0] & 0xFF));
	
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
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
//!rename typemesh

void	color_with_light(t_color *mesh_color,
	t_color *light_color, double intensity, t_color *new_color)
{
	t_color	scaled_color;

	scale_color(light_color, intensity,
		&scaled_color);
	get_average_color(&scaled_color, mesh_color, new_color);
	scale_color(new_color, intensity, new_color);
}

void	get_local_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector	scaled_vect;

	scale_vector(ray->dir_vect.axis, t, inter_pt->axis);
}

double	calculate_light_attenuation(t_ray *light_ray, double intensity)
{
	double			light_mag;
	const double	kc = 1.0;
	const double	kl = 45e-4;
	const double	kq = 75e-25;

	light_mag = get_vector_magnitude(light_ray->dir_vect.axis);
	return (intensity / (kc + kl * light_mag + kq * light_mag * light_mag));
}

void	add_self_shadowing(double light_coef, double light_attenuation,
	t_color *color)
{
	t_color	scaled_color;

	scale_color(color, 1 - light_attenuation * 4, &scaled_color);	
	subtract_color(color, &scaled_color, color);	
}

void	add_shading( t_ray *ray, t_ray_vector *normal,
	t_color *color, t_color *res_color)
{
	double	light_coef;
	t_color scaled_color;

	light_coef = scalar_product(ray->dir_vect.axis, normal->axis);
	normalize_zero_one(&light_coef);
	scale_color(color, light_coef, &scaled_color);
	subtract_color(color, &scaled_color, res_color);
}

void	add_lightening(t_add_lightening_params *params)
{
	t_ray	light_ray_sav;
	t_color	subt_color;
	t_color scaled_color;

	light_ray_sav = *params->light_ray;
	normalize_vector(params->light_ray->dir_vect.axis);
	*params->light_coef = scalar_product(params->light_ray->dir_vect.axis,
			params->normal->axis);
	normalize_zero_one(params->light_coef);
	subtract_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255},
		params->color, &subt_color);
	*params->light_attenuat = calculate_light_attenuation(&light_ray_sav,
			*params->light_coef * params->spotlight->intensity);
	scale_color(&subt_color, *params->light_attenuat * .0125, &scaled_color);
	add_color(&scaled_color, params->color, params->res_color);
}




int	get_sphere_color(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;
	t_color			spotlighty_color;
	double			light_attenuat;
	double			light_coef;	

	get_intersect_point(params->ray, params->t, &light_ray.origin_vect);
	subtract_vector(light_ray.origin_vect.axis,
		((t_sphere *) params->mesh)->origin_vect.axis, normal.axis);
	normalize_vector(normal.axis);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	color_with_light(&((t_sphere *) params->mesh)->color,
		&params->data->ambiant_light.color, params->data->ambiant_light.intensity, &ambiantly_color);
	color_with_light(&((t_sphere *) params->mesh)->color,
		&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255}, params->data->spotlight.intensity, &spotlighty_color);
	if (((t_sphere *) params->mesh)->which_t == 2)
		symmetrize_vector(normal.axis);
	add_shading(params->ray, &normal, &ambiantly_color, &ambiantly_color);
	add_shading(params->ray, &normal, &spotlighty_color, &spotlighty_color);



	if (has_shadow(params->data, (t_sphere *) params->mesh, &light_ray)
	|| is_sphere_surface_between(params->mesh, &params->data->spotlight))
		
		return (*params->color = ambiantly_color, 0);
	//|| ( scalar_product(normal.axis, tmp_ray.dir_vect.axis) < 0.0
	 //&& ((t_sphere *) params->mesh)->which_t == 2))	
	add_lightening(&(t_add_lightening_params){&light_ray, &normal,
		&params->data->spotlight, &spotlighty_color,  &spotlighty_color,
		&light_attenuat, &light_coef});
	add_self_shadowing(light_coef, light_attenuat, &spotlighty_color);
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	limit_to_255(params->color);
	return (0);
} 

void	get_plane_color(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;
	double view_dot_normal;
	t_color			spotlighty_color;
	t_plane		*plane;
	double			light_attenuat;
	double			light_coef;	 
	plane = ((t_plane *) params->mesh);

	cast_vector_mat_ray(&plane->norm_vect, &normal);
	get_intersect_point(params->ray, params->t, &light_ray.origin_vect);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	normalize_vector(params->ray->dir_vect.axis);
	view_dot_normal = scalar_product(normal.axis, params->ray->dir_vect.axis);
	if (view_dot_normal > 0)
		symmetrize_vector(normal.axis);
	

	color_with_light(&plane->color,
		&params->data->ambiant_light.color, params->data->ambiant_light.intensity, &ambiantly_color);
	color_with_light(&plane->color,
		&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255 }, params->data->spotlight.intensity, &spotlighty_color);
	add_shading(params->ray, &normal, &ambiantly_color, &ambiantly_color);
	add_shading(params->ray, &normal, &spotlighty_color, &spotlighty_color);
	light_coef = scalar_product(normal.axis, light_ray.dir_vect.axis);
	if (has_shadow(params->data, params->mesh, &light_ray) || light_coef < 1e-3)
	{
		*params->color = ambiantly_color;
		return ;
	}
	add_lightening(&(t_add_lightening_params){&light_ray, &normal,
		&params->data->spotlight, &spotlighty_color,  &spotlighty_color,
		&light_attenuat, &light_coef});
	add_self_shadowing(light_coef, light_attenuat, &spotlighty_color);
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	limit_to_255(params->color);
}

void	put_pxl_alpha(t_mlx *mlx, int x, int y, unsigned int alpha_color, void *img_ptr)
{
	const double	inverse_eight = 0.125;
	int				pxl_pos;

	int bpp, line_len;
	char *img_data = mlx_get_data_addr(img_ptr, &bpp,
		&line_len, &(int){0});

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl_pos = x * mlx->img.bpp * inverse_eight + y * mlx->img.line_len;
		int pxl_pos2 = (x - (WIDTH - 792))  * bpp * inverse_eight + (y - (HEIGHT - 200)) * line_len;
		// if (*(unsigned int *)(img_data + pxl_pos2) == 0x37A75D
		// 	|| *(unsigned int *)(img_data + pxl_pos2) == 0x449A61
		// 	|| *(unsigned int *)(img_data + pxl_pos2) == 0x6D863B
		// 	|| *(unsigned int *)(img_data + pxl_pos2) == 0x4A9463
		// 	|| *(unsigned int *)(img_data + pxl_pos2) == 0x34362E
		//  || *(unsigned int *)(img_data + pxl_pos2) == 0x67754)	
		if (*(unsigned int *)(img_data + pxl_pos2) != 0x0)		
		{			
			*(unsigned int *)(mlx->img.img_data + pxl_pos) = 
			*(unsigned int *)(img_data + pxl_pos2);
		}
	}
}

void	add_xpm_logo(t_mlx *mlx, int x, int y, void *img_ptr)
{
	const double	inverse_eight = 0.125;
	int				pxl_pos;

	int bpp, line_len;
	char *img_data = mlx_get_data_addr(img_ptr, &bpp,
		&line_len, &(int){0});

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl_pos = x * mlx->img.bpp * inverse_eight + y * mlx->img.line_len;
		int pxl_pos2 = x * bpp * inverse_eight + y * line_len;
		if (*(unsigned int *)(img_data + pxl_pos2) != 0xFF0000)			
		{			
			*(unsigned int *)(mlx->img.img_data + pxl_pos) = 
			*(unsigned int *)(img_data + pxl_pos2);
		}
	}
}

void	add_xpm_sph(t_mlx *mlx, int x, int y, void *img_ptr)
{
	const double	inverse_eight = 0.125;
	int				pxl_pos;

	int bpp, line_len;
	char *img_data = mlx_get_data_addr(img_ptr, &bpp,
		&line_len, &(int){0});

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl_pos = x * mlx->img.bpp * inverse_eight + y * mlx->img.line_len;
		int pxl_pos2 = (x - (WIDTH - 100)) * bpp * inverse_eight + y * line_len;
		if (*(unsigned int *)(img_data + pxl_pos2) != 0xFF0000)			
		{			
			*(unsigned int *)(mlx->img.img_data + pxl_pos) = 
			*(unsigned int *)(img_data + pxl_pos2);
		}
	}
}

void	add_xpm(t_mlx *mlx, int x, int y, void *img)
{
	if (!img)    
		return (display_error("Error loading image\n"));		    
	put_pxl_alpha(mlx, x, y, 0x0, img);
}

void	launch_rays(t_mlx *mlx, t_data *data)
{
	int	x;
	int	y;
	void *img = mlx_xpm_file_to_image(mlx->connect, "lorem.xpm", &(int){0}, &(int){0});
	void *logo = mlx_xpm_file_to_image(mlx->connect, "logo.xpm", &(int){0}, &(int){0});
	void *sph = mlx_xpm_file_to_image(mlx->connect, "sph.xpm", &(int){0}, &(int){0});
	void *cam = mlx_xpm_file_to_image(mlx->connect, "cam.xpm", &(int){0}, &(int){0});
	void *bulb = mlx_xpm_file_to_image(mlx->connect, "bulb.xpm", &(int){0}, &(int){0});
	void *amb = mlx_xpm_file_to_image(mlx->connect, "amb.xpm", &(int){0}, &(int){0});

	y = -1;
	while (++y < data->cam.resol[1])
	{
		x = -1;
		while (++x < data->cam.resol[0])
		{	
			exec_launch_rays(mlx, data, x, y);
			if (x >= 0 && x <= 100 && y >= 0 && y < 100)
				add_xpm_logo(mlx, x, y, logo);
			if (x >= WIDTH - 100 && y >= 0 && y < 100)
			{
				if (data->event.actual_mode == E_CAM)
					add_xpm_sph(mlx, x, y, cam);
				else if (data->event.actual_mode == E_SPOTL)
					add_xpm_sph(mlx, x, y, bulb);
				else if (data->event.actual_mode == E_AMBL)
					add_xpm_sph(mlx, x, y, amb);
				else if (data->event.actual_mode == E_MESH)
					add_xpm_sph(mlx, x, y, sph);			 
			}					
			if (data->event.legend && x >= WIDTH - 792 && y >= HEIGHT - 200)
				add_xpm(mlx, x, y, img);			
		}		
	}
}

