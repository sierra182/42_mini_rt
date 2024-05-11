# include "x_mini_struct.h"
# include "x_matrix.h"

void	trsl_vector(t_matrix_vector *vect, double values[])
{
	t_matrix_vector applied_vect;
	t_matrix_vector	trsf_matrix[MTX];

	init_matrix(trsf_matrix);
	set_matrix_translate(trsf_matrix, values);
	apply_matrix(trsf_matrix, vect, &applied_vect);
	*vect = applied_vect;
}