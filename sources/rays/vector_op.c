
#include "x_mini_struct.h"

static void	add_vector(t_vector *a, t_vector *b, t_vector *sum_vect)
{
	int			i;

	i = -1;
	while (++i < AXIS)
		sum_vect->axis[i] = a->axis[i] + b->axis[i];
}

static void	scale_vector(t_vector *a, double scaler, t_vector *scaled_vect)
{
	int			i;

	i = -1;
	while (++i < AXIS)
		scaled_vect->axis[i] = a->axis[i] * scaler;
}

void	scale_and_add_vectors(t_cam *cam, t_ray *ray, double norm_scale_x,
	double norm_scale_y)
{
	t_vector	scaled_up;
	t_vector 	scaled_right;
	t_vector	scaled_forward;
	t_vector	tmp_sum_vect;

	scale_vector(&cam->up_vect, norm_scale_y, &scaled_up);
	scale_vector(&cam->right_vect, norm_scale_x, &scaled_right);
	scale_vector(&cam->forward_vect, cam->focal_len, &scaled_forward);
	add_vector(&scaled_up, &scaled_right, &tmp_sum_vect);
	add_vector(&scaled_forward, &tmp_sum_vect, &ray->dir_vect);	
}
