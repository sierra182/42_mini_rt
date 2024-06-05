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
	double angle = 5;

	point.axis[0] = cyl->origin_vect.axis[0];
	point.axis[1] = cyl->origin_vect.axis[1];	
	point.axis[2] = cyl->origin_vect.axis[2];
	
	// if (cyl_nbr < 24)
	// {
	// 	axe[0] = 0;
	// 	axe[1] = 1;
	// 	axe[2] = 0;
	// 	rotate_mesh(&cyl->axis_vect, angle, axe);
	// }
	// else if (cyl_nbr < 40)
	{
		axe[0] = 0;
		axe[1] = 1;
		axe[2] = 0;
		rotate_mesh(&cyl->axis_vect, angle, axe);
	}
	

	symmetrize_vector(point.axis);
	


}