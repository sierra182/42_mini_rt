# include "se_mini_struct.h"
# include "x_matrix.h"

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);
void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);
double	*symmetrize_vector(double vect[]);


/**========================================================================
 *                           VIDEO_ROTATE_ELEMENT
 * for a 2 seconds video, generate 48 images
 * rotate 7.5 angle each frame
 *========================================================================**/
void	video_rotate_spheres(t_sphere *sphere, int obj_num)
{

	int axe[3];
	t_matrix_vector	trsf_matrix[MTX];
	t_matrix_vector applied_vect;
	double angle = 5;
	if (obj_num %2 == 0)
		angle = -5;

	t_ray_vector point;


	point.axis[0] = -45;
	point.axis[1] = 0;
	point.axis[2] = -45;
	
	
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

void	video_rotate_cylinders(t_cylinder *cyl, int obj_num, int cyl_nbr)
{
	// if (obj_num < 24)
	// {
	// 	return ;
	// }

	static int i = 0;
	static int j = -1;
	if (i % 360 * cyl_nbr == 0)
	{
		j = -j;
	}
	int axe[3];
	t_matrix_vector	trsf_matrix[MTX];
	t_matrix_vector applied_vect;
	double angle = 3;
	if (obj_num %2 == 0)
		angle = -3;

	t_ray_vector point;

	point.axis[0] = -45;
	point.axis[1] = 0;	
	point.axis[2] = -45;
	
	trsl_mesh(NULL, &cyl->origin_vect, point.axis);


	axe[0] = 1;
	axe[1] = 0;
	axe[2] = 0;
	rotate_mesh(&cyl->axis_vect, angle, axe);
	// printf("After X rotation: (%f, %f, %f)\n", cyl->origin_vect.axis[0], cyl->origin_vect.axis[1], cyl->origin_vect.axis[2]);
	axe[0] = 0;
	axe[1] = 1;
	axe[2] = 0;
	rotate_mesh(&cyl->axis_vect, angle, axe);
    // printf("After Y rotation: (%f, %f, %f)\n", cyl->origin_vect.axis[0], cyl->origin_vect.axis[1], cyl->origin_vect.axis[2]);
	axe[0] = 0;
	axe[1] = 0;
	axe[2] = 1;
	rotate_mesh(&cyl->axis_vect, angle, axe);
	// printf("After Z rotation: (%f, %f, %f)\n", cyl->origin_vect.axis[0], cyl->origin_vect.axis[1], cyl->origin_vect.axis[2]);

	symmetrize_vector(point.axis);
	trsl_mesh(NULL, &cyl->origin_vect, point.axis);
	printf("%i\n", j);
	
	if (j == 1)
	{
		cyl->color.rgb[0] += 4;
		cyl->color.rgb[1] -= 4;
	}
	else
	{
		cyl->color.rgb[0] -= 4;
		cyl->color.rgb[1] += 4;
	}
	// printf("Color: %i, %i, %i\n", cyl->color.rgb[0], cyl->color.rgb[1], cyl->color.rgb[2]);
	i++;
}