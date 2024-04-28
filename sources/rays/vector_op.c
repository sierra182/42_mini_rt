
#include "x_mini_struct.h"

static t_vector	add_vector(t_vector a, t_vector b)
{
	t_vector	sum_vect;
	int			i;

	i = -1;
	while (++i < AXIS)
		sum_vect.axis[i] = a.axis[i] + b.axis[i];
	return (sum_vect);
}

static t_vector	scale_vector(t_vector *a, double scaler)
{
	t_vector	scaled_vect;
	int			i;

	i = -1;
	while (++i < AXIS)
		scaled_vect.axis[i] = a->axis[i] * scaler;
	return (scaled_vect);
}

t_vector	scale_and_add_vectors(t_cam *cam, double norm_scale_x,
	double norm_scale_y)
{
	t_vector	scaled_up;
	t_vector 	scaled_right;
	t_vector	scaled_forward;

	scaled_up = scale_vector(cam->up_vect, norm_scale_y);
	scaled_right = scale_vector(cam->right_vect, norm_scale_x);
	scaled_forward = scale_vector(cam->forward_vect, cam->focal_len);
	return (add_vector(scaled_forward,
			add_vector(scaled_up, scaled_right)));
}