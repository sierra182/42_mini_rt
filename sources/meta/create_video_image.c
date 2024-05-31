# include "x_mini_struct.h"
# include "x_matrix.h"

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);
void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);
double	*symmetrize_vector(double vect[]);


/**========================================================================
 *                           VIDEO_ROTATE_ELEMENT
 * for a 2 seconds video, generate 48 images
 * rotate 7.5 angle each frame
 *========================================================================**/
void	video_rotate_element(t_sphere *sphere, int obj_num)
{
	int i = 0;
	int axe[3];
	t_matrix_vector	trsf_matrix[MTX];
	t_matrix_vector applied_vect;
	double angle = 5;

	t_ray_vector point;
	t_ray_vector point2;

	point.axis[0] = 10;
	point.axis[1] = 0;
	point.axis[2] = 0;
	
	
	trsl_mesh(NULL, &sphere->origin_vect, point.axis);


	axe[0] = 1;
	axe[1] = 0;
	axe[2] = 0;
	rotate_mesh(&sphere->origin_vect, angle, axe);
	axe[0] = 0;
	axe[1] = 1;
	axe[2] = 0;
	rotate_mesh(&sphere->origin_vect, angle, axe);
	axe[0] = 0;
	axe[1] = 0;
	axe[2] = 1;
	rotate_mesh(&sphere->origin_vect, angle, axe);

	symmetrize_vector(point.axis);
	trsl_mesh(NULL, &sphere->origin_vect, point.axis);

}