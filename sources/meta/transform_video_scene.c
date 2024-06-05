# include "se_mini_struct.h"
# include "x_matrix.h"

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);
void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);
double	*symmetrize_vector(double vect[]);
void	rotate_cam(t_cam *cam, double angle, int axe[]);
void	trsl_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	trsl_about_cam(t_cam *cam, t_matrix_vector *vect, double values[]);

void	video_trans_mesh(void *mesh, int mesh_num, int mesh_nbr)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)mesh;

	if (mesh_num < 24)
		return ;
	// printf("translating cylinder %d\n", mesh_num);
	trsl_mesh(NULL, &cyl->origin_vect, (double[3]){0, 0, -1});
	// rotate_mesh(&cyl->origin_vect, 5, (int[3]){0, 1, 0});
	// cyl->height -= 1;
}

void	video_rotate_cogs(t_cylinder *cyl, int	i, int cyl_nbr)
{
	int axe[3];
	t_ray_vector point;
	double angle = -3.33;
	
	static int k = 0;
	static int j = 1;
	// if (k % 48 * cyl_nbr == 0)
	// {
	// 	j = -j;
	// }

	// point.axis[0] = cyl->origin_vect.axis[0];
	// point.axis[1] = cyl->origin_vect.axis[1];	
	// point.axis[2] = cyl->origin_vect.axis[2];
	
	// if (i < 24)
	// {
	// 	angle = 2;
	// 	axe[0] = 0;
	// 	axe[1] = 1;
	// 	axe[2] = 0;
	// 	rotate_mesh(&cyl->axis_vect, angle, axe);
	// }
	// else if (i < 40)
	// {
	// 	axe[0] = 0;
	// 	axe[1] = 1;
	// 	axe[2] = 0;
	// 	rotate_mesh(&cyl->axis_vect, angle, axe);
	// }
	// else if (i < 56)
	// {
	// 	axe[0] = 0;
	// 	axe[1] = 0;
	// 	axe[2] = 1;
	// 	rotate_mesh(&cyl->axis_vect, angle, axe);
	// }
	// else if (i % 3 == 0)
	// {
		point.axis[0] = 0;
		point.axis[1] = 60;	
		point.axis[2] = 0;

		// t_matrix_vector trsf_matrix[MTX];
		// trsf_matrix[0] = 0;
		// trsf_matrix[1] = 60;
		// trsf_matrix[2] = 0;

		// trsl_mesh(NULL, &trsf_matrix, point.axis);


		axe[0] = 1;
		axe[1] = 0;
		axe[2] = 0;
		rotate_mesh(&cyl->axis_vect, angle, axe);
		axe[0] = 0;
		axe[1] = 1;
		axe[2] = 0;
		rotate_mesh(&cyl->axis_vect, angle, axe);
		axe[0] = 0;
		axe[1] = 0;
		axe[2] = 1;
		rotate_mesh(&cyl->axis_vect, angle, axe);

		// symmetrize_vector(point.axis);
		// trsl_mesh(NULL, &trsf_matrix, point.axis);


		printf("my color is: %d\n", cyl->color.rgb[0]);
		return ;
	// }

		
	
	angle = 2;
	printf("j: %d, k: %d, cyl_nbr: %d\n", j, k, cyl_nbr);
	// if (j == -1)
	// 	angle = -2;

	// trsl_cam(cam, &point, point.axis);

	axe[0] = 1;
	axe[1] = 0;
	axe[2] = 0;
	// rotate_mesh(&cyl->axis_vect, angle, axe);
	// symmetrize_vector(point.axis);
	// trsl_cam(cam, &point, point.axis);
	// symmetrize_vector(point.axis);

	
	k++;



}


void	rotate_pendulum(t_sphere *sphere, int i)
{
	int axe[3];
	double angle = 2;

	printf("i: %i\n", i);
	
	t_ray_vector point;

	point.axis[0] = 0;
	point.axis[1] = -60;
	point.axis[2] = 0;

	// point.axis[0] = sphere->origin_vect.axis[0];
	// point.axis[1] = sphere->origin_vect.axis[1] + 60;
	// point.axis[2] = sphere->origin_vect.axis[2];
	
	trsl_mesh(NULL, &sphere->origin_vect, point.axis);
	axe[0] = 1;
	axe[1] = 0;
	axe[2] = 0;
	rotate_mesh(&sphere->origin_vect, angle, axe);
	// axe[0] = 0;
	// axe[1] = 1;
	// axe[2] = 0;
	// rotate_mesh(&sphere->origin_vect, angle, axe);
	// axe[0] = 0;
	// axe[1] = 0;
	// axe[2] = 1;
	// rotate_mesh(&sphere->origin_vect, angle, axe);

	symmetrize_vector(point.axis);
	trsl_mesh(NULL, &sphere->origin_vect, point.axis);


}