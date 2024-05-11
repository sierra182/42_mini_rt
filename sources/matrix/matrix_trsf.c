# include "x_mini_struct.h"
# include <math.h>

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

void	set_matrix_scale(double matrix[][AXIS], double scale[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		matrix[i][i] = scale[i];
}

void	set_matrix_translate(t_matrix_vector matrix[], double trans[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		matrix[i].axis[AXIS] = trans[i];
}
