# include "x_mini_struct.h"
# include "x_matrix.h"


void	calculate_missing_vectors(t_cam *cam);
void	update_cam(t_cam *cam);
void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[])
{
	t_matrix_vector applied_vect;
	t_matrix_vector	trsf_matrix[MTX];
	printf("vect:%f, vect:%f, vect:%f\n", vect->axis[0], vect->axis[1], vect->axis[2]);

	init_matrix(trsf_matrix);
	set_matrix_translate(trsf_matrix, values);
	apply_matrix(trsf_matrix, vect, &applied_vect);
	printf("applied vect:%f, vect:%f, vect:%f\n", applied_vect.axis[0], applied_vect.axis[1], applied_vect.axis[2]);
	*vect = applied_vect;
	printf("renew vect:%f, vect:%f, vect:%f\n\n", vect->axis[0], vect->axis[1], vect->axis[2]);


	//update_cam(cam);
}

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[])
{
	t_matrix_vector	trsf_matrix[MTX];
	t_matrix_vector applied_vect;

	init_matrix(trsf_matrix);
	set_matrix_rotation(trsf_matrix, angle, axe);
	apply_matrix(trsf_matrix, vect, &applied_vect);
	*vect = applied_vect;
}