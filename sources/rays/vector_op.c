#include "vector_op.h"

void	normalize_vector(t_vector *vector)
{
	int		i;
	double	magnitude;

	magnitude = sqrt(pow(vector->axis[0], 2) + pow(vector->axis[1], 2)
			+ pow(vector->axis[2], 2));
	if (!magnitude)
		return ;
	i = -1;
	while (++i < AXIS)
		vector->axis[i] /= magnitude;
}

void	add_vector(t_vector *a, t_vector *b, t_vector *sum_vect)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		sum_vect->axis[i] = a->axis[i] + b->axis[i];
}

void	scale_vector(t_vector *vect, double scaler, t_vector *scaled_vect)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		scaled_vect->axis[i] = vect->axis[i] * scaler;
}

void	product_vector(t_vector *a, t_vector *b, t_vector *product_vect)
{
	product_vect->axis[0] = a->axis[1] * b->axis[2] - a->axis[2] * b->axis[1];
	product_vect->axis[1] = a->axis[2] * b->axis[0] - a->axis[0] * b->axis[2];
	product_vect->axis[2] = a->axis[0] * b->axis[1] - a->axis[1] * b->axis[0];
}

int	are_collinear_vectors(t_vector *pdct_vect, double precision)
{
	return (pdct_vect->axis[0] >= -precision && pdct_vect->axis[0] <= precision
		&& pdct_vect->axis[1] >= -precision && pdct_vect->axis[1] <= precision
		&& pdct_vect->axis[2] >= -precision && pdct_vect->axis[2] <= precision);
}
