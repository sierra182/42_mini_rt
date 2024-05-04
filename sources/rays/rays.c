#include "rays.h"

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
	t1 = (-b + sqrt(discrim)) / (2*a);
	// t2 = (-b - sqrt(discrim)) / (2*a)  
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

t_ray_vector *get_normal_vector(t_ray *ray, double t, t_sphere *sphere, t_ray_vector *normal)
{
	t_ray_vector inter_pt;
	// printf("color:t:, %f,  %f, %f, %f\n", t, inter_pt.axis[0], inter_pt.axis[1], inter_pt.axis[2]);
	// printf("sphere  %f, %f, %f\n", sphere->origin_vect.axis[0], sphere->origin_vect.axis[1], sphere->origin_vect.axis[2]);
	if (t <= 0.0)
		return (NULL);
	get_intersect_point(ray, t, &inter_pt);
	subtract_vector(&inter_pt, &sphere->origin_vect, normal);
	//printf("COLOR:t:, %f,  %f, %f,  %f\n", t, normal->axis[0], normal->axis[1], normal->axis[2]);
	normalize_vector(normal);
	//printf("COLOR2:t:, %f,  %f, %f,  %f\n", t, normal->axis[0], normal->axis[1], normal->axis[2]);
	int i = -1;
	while (++i < AXIS)
	{
		// if (normal->axis[i] < 0)
		// 	normal->axis[i] = -normal->axis[i];
		normal->axis[i] += 1;
		normal->axis[i] *= 0.5;
	}
	i = -1;
		while (++i < AXIS)
	{
		// if (normal->axis[i] < 0)
		// 	normal->axis[i] = -normal->axis[i];
		normal->axis[i] *= 255;
	
	}
	//printf("COLOR2:t:, %f,  %f, %f,  %f\n", t, normal->axis[0], normal->axis[1], normal->axis[2]);
	return (normal);
}

void	launch_rays(t_mlx *mlx, t_data *data)
{
	t_ray			ray;
	double			x;
	double			y;
	double			t1;
	t_ray_vector	*subt_vect;
	t_ray_vector 		color;

	y = -1;
	while (++y < data->cam.resol[1])
	{
		x = -1;
		while (++x < data->cam.resol[0])
		{
			new_ray(&data->cam, &ray, x, y);
			t1 = is_intersect_sphere(&ray, &data->spheres[0]);
			if (t1)
			{				
				get_normal_vector(&ray, t1, &data->spheres[0], &color);
				put_pxl(mlx, x, y, get_color(color.axis[0], color.axis[1], color.axis[2]));
			}
			else
				put_pxl(mlx, x, y, get_background_color(&ray));	
		}		
	}
}
