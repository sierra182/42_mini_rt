#include <math.h>
#include "x_mini_struct.h"

int	are_collinear_vectors(t_matrix_vector *cross_prdct, double precision)
{
	return (cross_prdct->axis[0] >= -precision
		&& cross_prdct->axis[0] <= precision
		&& cross_prdct->axis[1] >= -precision
		&& cross_prdct->axis[1] <= precision
		&& cross_prdct->axis[2] >= -precision
		&& cross_prdct->axis[2] <= precision);
}

int	get_axis_ratio(double a, double b, int *ratio)
{
	if (b)
		*ratio = a / b;
	else if (!a)
		*ratio = 1;
	else
		return (1);
	return (0);
}

int	are_collinear_vectors_diff_origin(double a[], double b[])
{
	int	k1;
	int	k2;
	int	k3;

	if (get_axis_ratio(a[0], b[0], &k1)
		|| get_axis_ratio(a[1], b[1], &k2)
		|| get_axis_ratio(a[2], b[2], &k3))
		return (0);
	return (k1 == k2 && k2 == k3);
}

void	cast_vector_mat_ray(t_matrix_vector *matrix_vect,
	t_ray_vector *ray_vect)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		ray_vect->axis[i] = matrix_vect->axis[i];
}

int	is_equal_vector(double a[], double b[])
{
	int	i;

	i = -1;
	while (++i < MTX)
		if (a[i] != b[i])
			return (0);
	return (1);
}
