#include "x_mini_struct.h"

void	init_matrix(t_vector matrix[])
{
	int	i;
	int	j;

	i = -1;
	while (++i < AXIS)
	{
		matrix[i].axis[i] = 1.0;
		j = -1;
		while (++j < AXIS)
			if (i != j)
				matrix[i].axis[j] = 0.0;
	}
}

void	set_matrix_translate(t_vector matrix[], double trans[])
{
	int	i;

	i = -1;
	while (++i < AXIS - 1)
		matrix[i].axis[AXIS - 1] = trans[i];
}

// void	set_matrix_scale(double matrix[][AXIS], double scale[])
// {
// 	int	i;

// 	i = -1;
// 	while (++i < AXIS - 1)
// 		matrix[i][i] = scale[i];
// }

// void	set_matrix_rotation(double matrix[][AXIS], double angle, int *axe)
// {
// 	angle *= M_PI / 180.0;
// 	if (axe[0])
// 	{
// 		matrix[1][1] = cos(angle);
// 		matrix[1][2] = -sin(angle);
// 		matrix[2][1] = sin(angle);
// 		matrix[2][2] = cos(angle);
// 	}
// 	else if (axe[1])
// 	{
// 		matrix[0][0] = cos(angle);
// 		matrix[0][2] = sin(angle);
// 		matrix[2][0] = -sin(angle);
// 		matrix[2][2] = cos(angle);
// 	}
// 	else if (axe[2])
// 	{
// 		matrix[0][0] = cos(angle);
// 		matrix[0][1] = -sin(angle);
// 		matrix[1][0] = sin(angle);
// 		matrix[1][1] = cos(angle);
// 	}
// }
static double	multiply_rowbycol(t_vector *a_row, t_vector b[], int col)
{
	double	rslt;
	int		i;

	rslt = 0;
	i = -1;
	while (++i < AXIS)
		rslt += a_row->axis[i] * b[i].axis[col];
	return (rslt);
}

void	multiply_matrix(t_vector a[], t_vector b[], t_vector mult_mat[])
{
	int	i;
	int	j;

	i = -1;
	while (++i < AXIS)
	{
		j = -1;
		while (++j < AXIS)
			mult_mat[i].axis[j] = multiply_rowbycol(&a[i], b, j);
	}
}

void	apply_matrix(t_vector matrix[], t_vector *vector, t_vector *rslt_vect)
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < AXIS)
	{
		rslt_vect->axis[i] = 0;
		j = -1;
		while (++j < AXIS)
			rslt_vect->axis[i] += (matrix[i].axis[j]
					* vector->axis[j]);
	}	
}

void	print_vector(t_vector vector)
{
	int	i;
		
	i = -1;
	while (++i < AXIS)	
		printf("%f ", vector.axis[i]);	
	printf("\n\n");
}

void	print_matrix(t_vector matrix[])
{
	int	i;
	int	j;
		
	i = -1;
	while (++i < AXIS)
	{
		j = -1;
		while (++j < AXIS)
			printf("%f ", matrix[i].axis[j]);
		printf("\n");
	}
	printf("\n");
}

void	matrix(t_cam *cam)
{
	t_vector	mult_matrix[AXIS];
	t_vector	rslt_vector;
	cam->right_vect.axis[3] = 0;
	cam->up_vect.axis[3] = 0;
	cam->forward_vect.axis[3] = 0;
	cam->origin_vect.axis[3] = 1;

	cam->cam_matrix[0] = cam->right_vect;
	cam->cam_matrix[1] = cam->up_vect;
	cam->cam_matrix[2] = cam->forward_vect;
	cam->cam_matrix[3] = cam->origin_vect;
	print_vector(cam->right_vect);
	print_vector(cam->up_vect);
	print_vector(cam->forward_vect);
	print_vector(cam->origin_vect);
	init_matrix(cam->trsf_matrix);
	set_matrix_translate(cam->trsf_matrix, (double []){0.2, 0, 0});
	print_matrix(cam->cam_matrix);
	print_matrix(cam->trsf_matrix);
	//multiply_matrix(cam->trsf_matrix, cam->cam_matrix, mult_matrix);
	print_vector(cam->origin_vect);
	apply_matrix(cam->trsf_matrix, &cam->cam_matrix[3], &rslt_vector);
	print_vector(rslt_vector);
	cam->origin_vect = rslt_vector;
	// cam->origin_vect.axis[0] = rslt_vector.axis[0];
	// cam->origin_vect.axis[1] = rslt_vector.axis[1];
	// cam->origin_vect.axis[2] = rslt_vector.axis[2];
	// cam->origin_vect.axis[3] = rslt_vector.axis[3];
}