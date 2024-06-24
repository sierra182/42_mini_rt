# include "se_mini_struct_bonus.h"
# include "x_matrix_bonus.h"

#define ANGLE_NEWTON 3

void	generate_video_frames(t_data *data);
void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);
void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);
double	*symmetrize_vector(double vect[]);
void	rotate_cam(t_cam *cam, double angle, int axe[]);
void	trsl_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	trsl_about_cam(t_cam *cam, t_matrix_vector *vect, double values[]);

void	newton_move_spheres(t_data *data)
{
	int axe[3];
	int obj_num = 0;
	double angle = -ANGLE_NEWTON;
	t_sphere *sphere;
	t_ray_vector point;
	
	
	printf("Newton's third law: For every action, there is an equal and opposite reaction.\n");
	if (obj_num == 0)
	{
		sphere = &data->spheres[obj_num];
		point.axis[0] = sphere->origin_vect.axis[0];
		point.axis[1] = sphere->origin_vect.axis[1];
		point.axis[2] = sphere->origin_vect.axis[2];


		trsl_mesh(NULL, &sphere->origin_vect, point.axis);
		// axe[0] = 1;
		// axe[1] = 0;
		// axe[2] = 0;
		// rotate_mesh(&sphere->origin_vect, angle, axe);
		// axe[0] = 0;
		// axe[1] = 1;
		// axe[2] = 0;
		// rotate_mesh(&sphere->origin_vect, angle, axe);
		axe[0] = 0;
		axe[1] = 0;
		axe[2] = 1;
		rotate_mesh(&sphere->origin_vect, angle, axe);

		symmetrize_vector(point.axis);
		trsl_mesh(NULL, &sphere->origin_vect, point.axis);

		obj_num++;
	}



}