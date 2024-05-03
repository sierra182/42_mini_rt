#include <math.h>
#include "x_mini_struct.h"

void	init_matrix(t_matrix_vector matrix[])
{
	int	i;
	int	j;

	i = -1;
	while (++i < MTX)
	{
		matrix[i].axis[i] = 1.0;
		j = -1;
		while (++j < MTX)
			if (i != j)
				matrix[i].axis[j] = 0.0;
	}
}

void	set_matrix_translate(t_matrix_vector matrix[], double trans[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		matrix[i].axis[AXIS] = trans[i];
}

// void	set_matrix_scale(double matrix[][AXIS], double scale[])
// {
// 	int	i;

// 	i = -1;
// 	while (++i < AXIS - 1)
// 		matrix[i][i] = scale[i];
// }

void	set_matrix_rotation(t_matrix_vector matrix[], double angle, int axe[])
{
	angle *= M_PI / 180.0;
	if (axe[0])
	{
		matrix[1].axis[1] = cos(angle);
		matrix[1].axis[2] = -sin(angle);
		matrix[2].axis[1] = sin(angle);
		matrix[2].axis[2] = cos(angle);
	}
	else if (axe[1])
	{
		matrix[0].axis[0] = cos(angle);
		matrix[0].axis[2] = sin(angle);
		matrix[2].axis[0] = -sin(angle);
		matrix[2].axis[2] = cos(angle);
	}
	else if (axe[2])
	{
		matrix[0].axis[0] = cos(angle);
		matrix[0].axis[1] = -sin(angle);
		matrix[1].axis[0] = sin(angle);
		matrix[1].axis[1] = cos(angle);
	}
}

static double	multiply_rowbycol(t_matrix_vector *a_row, t_matrix_vector b[], int col)
{
	double	rslt;
	int		i;

	rslt = 0;
	i = -1;
	while (++i < MTX)
		rslt += a_row->axis[i] * b[i].axis[col];
	return (rslt);
}

void	multiply_matrix(t_matrix_vector a[], t_matrix_vector b[], t_matrix_vector mult_mat[])
{
	int	i;
	int	j;

	i = -1;
	while (++i < MTX)
	{
		j = -1;
		while (++j < MTX)
			mult_mat[i].axis[j] = multiply_rowbycol(&a[i], b, j);
	}
}

void	apply_matrix(t_matrix_vector matrix[], t_matrix_vector *vector, t_matrix_vector *rslt_vect)
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < MTX)
	{	
		rslt_vect->axis[i] = 0.0;
		j = -1;
		while (++j < MTX)
			rslt_vect->axis[i] += (matrix[i].axis[j]
					* vector->axis[j]);
	}	
}

void	print_matrix_vector(t_matrix_vector vector)
{
	int	i;
		
	i = -1;
	while (++i < MTX)	
		printf("%f ", vector.axis[i]);	
	printf("\n\n");
}

void	print_matrix(t_matrix_vector matrix[])
{
	int	i;
	int	j;
		
	i = -1;
	while (++i < MTX)
	{
		j = -1;
		while (++j < MTX)
			printf("%f ", matrix[i].axis[j]);
		printf("\n");
	}
	printf("\n");
}
