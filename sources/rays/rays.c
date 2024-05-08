#include "rays.h"

void    is_intersect_plane(t_ray *ray, t_plane *plane, double *t);
void    is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder, double *t2);
void	subtract_torvec(t_matrix_vector *b, t_ray_vector *a, t_ray_vector *subt_vect);
void	subtract_color_color(t_color *a, t_color *b, t_color *subt_color);
void	add_color(t_color *a, t_color *b, t_color *sum_color);
void	scale_color_color(t_color *color, double scaler, t_color *scaled_color);

static void	scale_and_add_vectors(t_cam *cam, t_ray *ray, double norm_scale_x,
	double norm_scale_y)
{
	t_matrix_vector	scaled_up;
	t_matrix_vector	scaled_right;
	t_matrix_vector	scaled_forward;
	t_matrix_vector	tmp_sum_vect;

	scale_matrix_vector(&cam->up_vect, norm_scale_y, &scaled_up);
	scale_matrix_vector(&cam->right_vect, norm_scale_x, &scaled_right);
	scale_matrix_vector(&cam->forward_vect, cam->focal_len, &scaled_forward);
	add_matrix_vector(&scaled_up, &scaled_right, &tmp_sum_vect);
	add_matrix_to_ray_vector(&scaled_forward, &tmp_sum_vect, &ray->dir_vect);
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

	cast_vector(&cam->origin_vect, &ray->origin_vect);
	norm_scale_y = normalize_pixel(cam->resol[1], y, 0) * cam->scale;
	norm_scale_x = normalize_pixel(cam->resol[0], x, 1) * cam->scale
		* cam->aspect;
	scale_and_add_vectors(cam, ray, norm_scale_x, norm_scale_y);
	normalize_vector(&ray->dir_vect);
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
	t_ray_vector	SR;
	double			a;
	double			b;
	double			c;	
	double			discrim;
	double			t1;

	subtract_vector(&ray->origin_vect, &sphere->origin_vect, &SR);
	a = product_scalar(&ray->dir_vect, &ray->dir_vect);
	b = 2 * product_scalar(&SR, &ray->dir_vect);
	c = product_scalar(&SR, &SR) - sphere->square_radius;
	discrim = b * b - 4 * a * c;
	if (discrim < 0)
	    return (0.0);
	t1 = (-b - sqrt(discrim)) / (2*a); // t2 = (-b + sqrt(discrim)) / (2*a) 	 
	return (t1);
}

int	get_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char[])
		{r, g, b, 0});
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

	scale_ray_vector(&ray->dir_vect, t, &scaled_vect);
	add_ray_vector(&ray->origin_vect, &scaled_vect, inter_pt);	
}

int		is_behind_cam(double t)
{
	return (t <= 0.0);
}
void	get_normal_color(t_ray *ray, double t, t_sphere *sphere, t_color *color)
{
	t_ray_vector inter_pt;
	t_ray_vector normal;
	
	get_intersect_point(ray, t, &inter_pt);
	subtract_vector(&inter_pt, &sphere->origin_vect, &normal);
	normalize_vector(&normal);
	cast_vector_to_color(&normal, color);
}

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
// 	light_coef = product_scalar(&light_ray,&normal);
// 	light_coef = normalize_scalar_product(light_coef);
// 	scale_color(&sphere->color, light_coef, &scaled_vect);
// 	cast_vector_ray_to_color(&scaled_vect, color);
// }

void	get_sphere_normal_spotlight_color(t_ray *ray, double t, t_sphere *sphere, t_spotlight *spotlight, t_color *color)
{
	t_ray_vector	inter_pt;
	t_ray_vector	normal;
	t_ray_vector	light_ray;
	t_ray_vector	scaled_vect;
	double 			light_coef;
	t_color			subt_color;

	get_intersect_point(ray, t, &inter_pt);
	subtract_vector(&inter_pt, &sphere->origin_vect, &normal);
	normalize_vector(&normal);
	// subtract_vector(&inter_pt, &spotlight->origin_vect, &light_ray);
	subtract_torvec(&spotlight->origin_vect, &inter_pt, &light_ray);
	normalize_vector(&light_ray);
	light_coef = product_scalar(&light_ray,&normal);
	light_coef = normalize_scalar_product(light_coef);
	subtract_color_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255}, &sphere->color, &subt_color);
	
	scale_color(&subt_color, light_coef * spotlight->intensity, &scaled_vect);
	cast_vector_ray_to_color(&scaled_vect, color);
	add_color(color, &sphere->color, color);
	// scale_color(&sphere->color, light_coef, &scaled_vect);
	// cast_vector_ray_to_color(&scaled_vect, color);
}

void	color_with_ambiant_light(t_color *mesh_color, t_ambiant_light *ambiant_light, t_color *new_color)
{
	t_color			subt_color;
	t_color			ambiant_scaled_color;

	subtract_color_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255}, mesh_color, &subt_color);

	scale_color_color(&ambiant_light->color, ambiant_light->intensity, &ambiant_scaled_color);
	//scale_color_color(&ambiant_scaled_color, ambiant_light->intensity, &ambiant_scaled_color);

	// printf("ambiant color :%i, %i, %i\n", subt_color.rgb[0], subt_color.rgb[1], subt_color.rgb[2]);
	double tmp = ambiant_scaled_color.rgb[0] / 255.0;
	new_color->rgb[0] = tmp * subt_color.rgb[0] + mesh_color->rgb[0];
		// printf("ambiant 0 color :%i\n", new_color->rgb[0]);
	// if (new_color->rgb[0] > 255)
	// {
	// 	new_color->rgb[0] = 255;
	// }
	double tmp2 = ambiant_scaled_color.rgb[1] / 255.0;
	new_color->rgb[1] = tmp2 * subt_color.rgb[1] + mesh_color->rgb[1];
		// printf("ambiant 1 color :%i\n", new_color->rgb[1]);
	// if (new_color->rgb[1] > 255)
	// {
	// 	new_color->rgb[1] = 255;
	// }
	double tmp3 = ambiant_scaled_color.rgb[2] / 255.0;
	new_color->rgb[2] = tmp3 * subt_color.rgb[2] + mesh_color->rgb[2];
		// printf("ambiant 2 color :%i\n", new_color->rgb[2]);
	// if (new_color->rgb[2] > 255)
	// {
	// 	new_color->rgb[2] = 255;
	// }
}

void	get_plane_normal_spotlight_color(t_ray *ray, double t, t_plane *plane, t_spotlight *spotlight, t_color *color, t_sphere *sphere, t_ambiant_light *ambiant_light)
{	
	t_ray_vector	normal;
	t_ray			light_ray;
	t_ray_vector	scaled_vect;
	double 			light_coef;
	t_color			subt_color;
	t_color			ambiant_color;

	cast_vector(&plane->norm_vect, &normal);
	get_intersect_point(ray, t, &light_ray.origin_vect);
		// subtract_vector(&inter_pt, &plane->origin_vect, &normal);
	//normalize_vector(&normal);
	subtract_torvec(&spotlight->origin_vect, &light_ray.origin_vect, &light_ray.dir_vect);
	normalize_vector(&light_ray.dir_vect);
	color_with_ambiant_light(&plane->color, ambiant_light, &ambiant_color);
	//printf("ambiant color :%i, %i, %i\n", ambiant_color.rgb[0], ambiant_color.rgb[1], ambiant_color.rgb[2]);
	if (is_intersect_sphere(&light_ray, sphere))
	{		
		//*color = (t_color){.rgb[0] = 0, .rgb[1] = 0, .rgb[2] = 0};
		*color = ambiant_color;		
		return ;
	}
	light_coef = product_scalar(&normal, &light_ray.dir_vect);
	//light_coef = normalize_scalar_product(light_coef);
	
	subtract_color_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255}, &ambiant_color, &subt_color);

	scale_color(&subt_color, light_coef * spotlight->intensity, &scaled_vect);
	cast_vector_ray_to_color(&scaled_vect, color);
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
			is_intersect_plane(&ray, &data->planes[0], &t2);
			is_intersect_cylinder(&ray, &data->cylinders[0], &t3);
			// printf("t2: %f\n", t2);

			if (t && !is_behind_cam(t))
			{
				get_sphere_normal_spotlight_color(&ray, t, &data->spheres[0], &data->spotlight, &color);
				put_pxl(mlx, x, y, get_color(color.rgb[0], color.rgb[1], color.rgb[2]));
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
