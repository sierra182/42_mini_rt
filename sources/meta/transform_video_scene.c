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
	// cyl->height -= 1;
}