#include "vector_op.h"

void	normalize_vector(double vector[])
{
	int		i;
	double	magnitude;

	magnitude = sqrt(pow(vector[0], 2) + pow(vector[1], 2)
			+ pow(vector[2], 2));
	if (!magnitude)
		return ;
	i = -1;
	while (++i < AXIS)
		vector[i] /= magnitude;
}

double	normalize_zero_one(double scalar_product)
{
	return ((scalar_product + 1) * 0.5);
}

void	cross_product(t_matrix_vector *a, t_matrix_vector *b, t_matrix_vector *product_vect)
{
	product_vect->axis[0] = a->axis[1] * b->axis[2] - a->axis[2] * b->axis[1];
	product_vect->axis[1] = a->axis[2] * b->axis[0] - a->axis[0] * b->axis[2];
	product_vect->axis[2] = a->axis[0] * b->axis[1] - a->axis[1] * b->axis[0];
}

int	are_collinear_vectors(t_matrix_vector *pdct_vect, double precision)
{
	return (pdct_vect->axis[0] >= -precision && pdct_vect->axis[0] <= precision
		&& pdct_vect->axis[1] >= -precision && pdct_vect->axis[1] <= precision
		&& pdct_vect->axis[2] >= -precision && pdct_vect->axis[2] <= precision);
}

void	cast_vector_mat_ray(t_matrix_vector *matrix_vect, t_ray_vector *ray_vect)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		ray_vect->axis[i] = matrix_vect->axis[i];	
}
