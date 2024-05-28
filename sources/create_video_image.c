# include "x_mini_struct.h"
# include "x_matrix.h"

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);


/**========================================================================
 *                           VIDEO_ROTATE_ELEMENT
 * for a 2 seconds video, generate 48 images
 * rotate 7.5 angle each frame
 *========================================================================**/
void	video_rotate_element(t_sphere *sphere)
{
	int i = 0;
	int axe[3];
	t_matrix_vector	trsf_matrix[MTX];
	t_matrix_vector applied_vect;

	axe[0] = 0;
	axe[1] = -1;
	axe[2] = 0;
	
	
		init_matrix(trsf_matrix);
		set_matrix_rotation(trsf_matrix, 7.5, axe);
		apply_matrix(trsf_matrix, &sphere->origin_vect, &applied_vect);
		sphere->origin_vect = applied_vect;

	// axe[0] = 0;
	// axe[1] = 0;
	// axe[2] = 1;
	
	// 	init_matrix(trsf_matrix);
	// 	set_matrix_rotation(trsf_matrix, 7.5, axe);
	// 	apply_matrix(trsf_matrix, &sphere->origin_vect, &applied_vect);
	// 	sphere->origin_vect = applied_vect;
	// 	 printf("another i: %i\n", i);



}