#include <math.h>
#include "x_mini_struct.h"

void	invert_vector(double ori[], double dir[],
	double inv_ori[], double inv_dir[])
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
