# include "se_mini_struct.h"
# include "x_matrix.h"

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);
void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);
double	*symmetrize_vector(double vect[]);
void	rotate_cam(t_cam *cam, double angle, int axe[]);
void	trsl_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	trsl_about_cam(t_cam *cam, t_matrix_vector *vect, double values[]);



/**========================================================================
 *                           VIDEO_ROTATE_ELEMENT
 * for a 2 seconds video, generate 48 images
 * rotate 7.5 angle each frame
 *========================================================================**/
void	video_rotate_spheres(t_sphere *sphere, int obj_num, int sp_nbr)
{

	int axe[3];
	t_matrix_vector	trsf_matrix[MTX];
	t_matrix_vector applied_vect;
	double angle = 5;
	if (obj_num %2 == 0)
		angle = -5;
	static int i = 0;
	static int j = -1;
	if (sphere->color.rgb[0] == 0)
	{
		return ;
	}
	if (i % 360 * sp_nbr == 0)
	{
		j = -j;
	}

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

	if (j == 1)
	{
		if (obj_num %2 == 0)
		{
			sphere->color.rgb[0] -= 4;
			sphere->color.rgb[1] -= 4;
		}
		else
		{
			sphere->color.rgb[0] -= 4;
			sphere->color.rgb[2] -= 4;
		}
	}
	else
	{
		if (obj_num %2 == 0)
		{
			sphere->color.rgb[0] += 4;
			sphere->color.rgb[1] += 4;
		}
		else
		{
			sphere->color.rgb[0] += 4;
			sphere->color.rgb[2] += 4;
		}
	}
	i++;
}

void	video_rotate_cylinders(t_cylinder *cyl, int obj_num, int cyl_nbr)
{
	if (obj_num < 24)
	{
		return ;
	}

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
	axe[0] = 0;
	axe[1] = 1;
	axe[2] = 0;
	rotate_mesh(&cyl->axis_vect, angle, axe);
	axe[0] = 0;
	axe[1] = 0;
	axe[2] = 1;
	rotate_mesh(&cyl->axis_vect, angle, axe);

	symmetrize_vector(point.axis);
	trsl_mesh(NULL, &cyl->origin_vect, point.axis);
	
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
	i++;
}

void	video_rotate_cam(t_cam *cam)
{
	int axe[3];
	t_matrix_vector	trsf_matrix[MTX];
	t_matrix_vector applied_vect;
	double angle = 5;

	t_matrix_vector point;
	point.axis[0] = 0;
	point.axis[1] = 0;
	point.axis[2] = 20;
	
	trsl_cam(cam, &point, point.axis);
	axe[0] = 0;
	axe[1] = 1;
	axe[2] = 0;
	rotate_cam(cam, angle, axe);
	// axe[0] = 0;
	// axe[1] = 1;
	// axe[2] = 0;
	// rotate_mesh(&sphere->origin_vect, angle, axe);
	// axe[0] = 0;
	// axe[1] = 0;
	// axe[2] = 1;
	// rotate_mesh(&sphere->origin_vect, angle, axe);

	symmetrize_vector(point.axis);
	trsl_cam(cam, &point, point.axis);
}


void	video_rotate_cam2(t_cam *cam)
{
	t_ray_vector point;
	int axe[3];
	t_matrix_vector	trsf_matrix[MTX];
	t_matrix_vector applied_vect;
	double angle = 3;

	point.axis[0] = 45;
	point.axis[1] = 0;	
	point.axis[2] = 45;

	printf("rotate camera\n");
	trsl_cam(cam, &cam->origin_vect, point.axis);
	// axe[0] = 1;
	// axe[1] = 0;
	// axe[2] = 0;
	// rotate_cam(cam, angle, axe);
	axe[0] = 0;
	axe[1] = 1;
	axe[2] = 0;
	rotate_cam(cam, angle, axe);
	// axe[0] = 0;
	// axe[1] = 0;
	// axe[2] = 1;
	// rotate_cam(cam, angle, axe);
	symmetrize_vector(point.axis);
	trsl_cam(cam, &cam->origin_vect, point.axis);
	printf("cam position: %f %f %f\n", cam->origin_vect.axis[0], cam->origin_vect.axis[1], cam->origin_vect.axis[2]);
}

// void video_rotate_cam(t_cam *cam)
// {
//     t_ray_vector point;
//     int axe[3];
//     double angle = 3;

//     // Point central autour duquel on veut tourner
//     point.axis[0] = 45;
//     point.axis[1] = 0;
//     point.axis[2] = 45;

//     printf("rotate camera\n");

//     // Translate la caméra pour que le point central devienne l'origine
//     double to_origin[3] = {
//         -point.axis[0],
//         -point.axis[1],
//         -point.axis[2]
//     };
//     trsl_mesh(NULL, &cam->origin_vect, to_origin);

//     // Rotation autour de l'axe Y (axe vertical)
//     axe[0] = 0;
//     axe[1] = 1;
//     axe[2] = 0;
//     rotate_cam(cam, angle, axe);

//     // Translate la caméra pour la remettre à sa position initiale
//     double back_to_position[3] = {
//         point.axis[0],
//         point.axis[1],
//         point.axis[2]
//     };
//     trsl_mesh(NULL, &cam->origin_vect, back_to_position);
// }