#include "rays.h"
# include <math.h>
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
	if (x_flag)
		return (((pixel + 0.5) / screen_size) * 2 - 1);
	return ((1 - 2 * (pixel + 0.5) / screen_size));
}

static void	new_ray(t_cam *cam, int x, int y, t_ray *ray)
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

static void	calculate_missing_vectors(t_cam *cam)
{
	normalize_vector(&cam->forward_vect);
	cam->up_vect.axis[0] = 0;
	cam->up_vect.axis[1] = 1;
	cam->up_vect.axis[2] = 0;
	product_vector(&cam->up_vect, &cam->forward_vect, &cam->right_vect);
	if (are_collinear_vectors(&cam->right_vect, 1e-3))
	{
		cam->up_vect.axis[0] = -1;
		cam->up_vect.axis[1] = 0;
		cam->up_vect.axis[2] = 0;
		product_vector(&cam->up_vect, &cam->forward_vect, &cam->right_vect);
	}
	normalize_vector(&cam->right_vect);
	product_vector(&cam->forward_vect, &cam->right_vect, &cam->up_vect);
	normalize_vector(&cam->up_vect);
}

void	launch_rays(t_cam *cam)
{
	t_ray	ray;
	double	aspect;
	double	scale;
	int		x;
	int		y;

	calculate_missing_vectors(cam);
	cam->scale = tan(cam->fov / 2);
	cam->aspect = cam->resol[0] / cam->resol[1];
	y = -1;
	while (++y < cam->resol[1])
	{
		x = -1;
		while (++x < cam->resol[0])
			new_ray(cam, x, y, &ray);
	}
}
