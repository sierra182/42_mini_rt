#include "vector_op.h"
static void	normalize_vector(t_vector *vector);

static void	add_vector(t_vector *a, t_vector *b, t_vector *sum_vect)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		sum_vect->axis[i] = a->axis[i] + b->axis[i];
}

static void	scale_vector(t_vector *a, double scaler, t_vector *scaled_vect)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		scaled_vect->axis[i] = a->axis[i] * scaler;
}

void	product_vector(t_vector *a, t_vector *b, t_vector *product_vect)
{
	product_vect->axis[0] = a->axis[1] * b->axis[2] - a->axis[2] * b->axis[1];
	product_vect->axis[1] = a->axis[2] * b->axis[0] - a->axis[0] * b->axis[2];
	product_vect->axis[2] = a->axis[0] * b->axis[1] - a->axis[1] * b->axis[0];
}

void	calculate_up_right_vectors(t_cam *cam)
{
	cam->up_vect.axis[0] = 0;
	cam->up_vect.axis[1] = 1;
	cam->up_vect.axis[2] = 0;
	product_vector(&cam->up, &cam->forward, &cam->right_vect);
	normalize_vector(&cam->right_vect);
	product_vector(&cam->forward, &cam->right, &cam->up);
	normalize_vector(&cam->up);
}

void	scale_and_add_vectors(t_cam *cam, t_ray *ray, double norm_scale_x,
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
