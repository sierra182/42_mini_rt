#ifndef X_MATRIX_H
# define X_MATRIX_H

# include "x_mini_struct.h"

void	init_matrix(t_matrix_vector matrix[]);
void	multiply_matrix(t_matrix_vector a[], t_matrix_vector b[],
	t_matrix_vector mult_matrix[]);
void	apply_matrix(t_matrix_vector matrix[], t_matrix_vector *vector,
	t_matrix_vector *applied_vect);
void	set_matrix_translate(t_matrix_vector matrix[], double trans[]);
void	set_matrix_scale(double matrix[][AXIS], double scale[]);
void	set_matrix_rotation(t_matrix_vector matrix[], double angle, int axe[]);

#endif