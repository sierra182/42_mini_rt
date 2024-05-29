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
void	add_xpm_items(t_mlx *mlx, t_data *data, int x, int y);

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

int	is_behind_cam(double t)
{
	return (t <= 0.0);
}

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector	scaled_vect;

	scale_vector(ray->dir_vect.axis, t, scaled_vect.axis);
	add_vector(ray->origin_vect.axis, scaled_vect.axis, inter_pt->axis);
}

void	get_local_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector	scaled_vect;

	scale_vector(ray->dir_vect.axis, t, inter_pt->axis);
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
		{	
			exec_launch_rays(mlx, data, x, y);
			add_xpm_items(mlx, data, x, y);
		}		
	}
}

