#include "rays.h"

static void	scale_and_add_vectors(t_cam *cam, t_ray *ray, double norm_scale_x,
	double norm_scale_y)
{
	t_vector	scaled_up;
	t_vector	scaled_right;
	t_vector	scaled_forward;
	t_vector	tmp_sum_vect;

	scale_vector(&cam->up_vect, norm_scale_y, &scaled_up);
	scale_vector(&cam->right_vect, norm_scale_x, &scaled_right);
	scale_vector(&cam->forward_vect, cam->focal_len, &scaled_forward);
	add_vector(&scaled_up, &scaled_right, &tmp_sum_vect);
	add_vector(&scaled_forward, &tmp_sum_vect, &ray->dir_vect);
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

	ray->origin_vect = cam->origin_vect;
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
#include <stdio.h>
int	is_intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vector	SR;
	double		a;
	double		b;
	double		c;	
	double		discrim;

	subtract_vector(&ray->origin_vect, &sphere->origin_vect, &SR);
	a = product_scalar(&ray->dir_vect, &ray->dir_vect);
	b = 2 * product_scalar(&SR, &ray->dir_vect);
	c = product_scalar(&SR, &SR) - sphere->square_radius;
	discrim = b * b - 4 * a * c;
	if (discrim < 0)
	    return (0);
			// printf("IN INTERSECT");
	// t1 = (-b + sqrt(discriminant)) / (2*a)
	// t2 = (-b - sqrt(discriminant)) / (2*a)  
	return (1);
}

void	launch_rays(t_mlx *mlx, t_data *data)
{
	t_ray	ray;
	double		x;
	double		y;
// printf("IN Launch :%f, %f", data->cam.resol[1], data->cam.resol[0]);
	y = -1;
	while (++y < data->cam.resol[1])
	{
		x = -1;
		while (++x < data->cam.resol[0])
		{///	printf("IN LOOP");
			new_ray(&data->cam, &ray, x, y);
			if (data->spheres && is_intersect_sphere(&ray, &data->spheres[0]))
				put_pxl(mlx, x, y, *(int *)(unsigned char[])
					{225, 125, 125, 0});		
		}		
	}
}
