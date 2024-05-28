# include <math.h>
# include "x_mini_struct.h"

void	invert_vector(double ori[], double dir[], double inv_ori[], double inv_dir[])
{	
	int	i;

	i = -1;
	while (++i < AXIS)
	{
		inv_ori[i] = ori[i] + dir[i];
		inv_dir[i] = -dir[i];
	}
}

double	*symmetrize_vector(double vect[])
{	
	int	i;

	i = -1;
	while (++i < AXIS)	
		vect[i] = -vect[i];
	return (vect);
}


double	get_vector_magnitude(double vector[])
{
	return (sqrt(pow(vector[0], 2) + pow(vector[1], 2)
			+ pow(vector[2], 2)));
}

void	normalize_vector(double vector[])
{
	int		i;
	double	magnitude;
	double	inverse_mag;

	magnitude = get_vector_magnitude(vector);
	if (!magnitude)
		return ;
	inverse_mag = 1 / magnitude;
	i = -1;
	while (++i < AXIS)
		vector[i] *= inverse_mag;
}

void	normalize_zero_one(double *scalar_product)
{
	*scalar_product = (*scalar_product + 1) * 0.5;
}

int	are_collinear_vectors(t_matrix_vector *cross_prdct, double precision)
{
	return (cross_prdct->axis[0] >= -precision && cross_prdct->axis[0] <= precision
		&& cross_prdct->axis[1] >= -precision && cross_prdct->axis[1] <= precision
		&& cross_prdct->axis[2] >= -precision && cross_prdct->axis[2] <= precision);
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
	int k1;
	int	k2;
	int	k3;
	
	if (get_axis_ratio(a[0], b[0], &k1)
		|| get_axis_ratio(a[1], b[1], &k2) 
		|| get_axis_ratio(a[2], b[2], &k3))
		return (0);
	return (k1 == k2 && k2 == k3);
}

void	cast_vector_mat_ray(t_matrix_vector *matrix_vect, t_ray_vector *ray_vect)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		ray_vect->axis[i] = matrix_vect->axis[i];	
}