#include "x_mini_struct.h"

void    add_vector(double a[], double b[], double sum_vect[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		sum_vect[i] = a[i] + b[i];
}

void	subtract_vector(double a[], double b[], double subt_vect[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		subt_vect[i] = a[i] - b[i];
}

void	scale_vector(double vect[], double scaler, double scaled_vect[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		scaled_vect[i] = vect[i] * scaler;
}

void	add_color(t_color *a, t_color *b, t_color *sum_color)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		sum_color->rgb[i] = a->rgb[i] + b->rgb[i];
}

void	subtract_color(t_color *a, t_color *b, t_color *subt_color)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		subt_color->rgb[i] = a->rgb[i] - b->rgb[i];
}

void	scale_color(t_color *color, double scaler, t_color *scaled_color)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		scaled_color->rgb[i] = color->rgb[i] * scaler;
}

double	scalar_product(double a[], double b[])
{
	double scalar;	
	int	i;

	scalar = 0.0;
	i = -1;
	while (++i < AXIS)
		scalar += a[i] * b[i];
	return (scalar);
}