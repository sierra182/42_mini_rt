#include <math.h>
#include "se_mini_struct.h"

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

void	self_normalize_vector(double vector[])
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

void	normalize_vector(double vector[], double magnitude, double norm_vect[])
{
	int		i;
	double	inverse_mag;

	if (!magnitude)
		return ;
	inverse_mag = 1 / magnitude;
	i = -1;
	while (++i < AXIS)
		norm_vect[i] *= inverse_mag;
}

void	normalize_zero_one(double *scalar_product, int clamp_flag)
{
	if (!clamp_flag)
		*scalar_product = (*scalar_product + 1) * 0.5;
	else if (*scalar_product >= -1 && *scalar_product < 0)
		*scalar_product = 0;
}
