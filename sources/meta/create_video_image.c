# include "se_mini_struct.h"
# include "x_matrix.h"

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);
void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);
double	*symmetrize_vector(double vect[]);
void	rotate_cam(t_cam *cam, double angle, int axe[]);
void	trsl_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	trsl_about_cam(t_cam *cam, t_matrix_vector *vect, double values[]);

#define ANGLE 3

void update_color(t_color *color, int increment)
{
    for (int i = 1; i < 3; i++)
	{
        color->rgb[i] += increment;
        if (color->rgb[i] > 255) {
            color->rgb[i] = 255;
        } else if (color->rgb[i] < 0) {
            color->rgb[i] = 0;
        }
    }
}

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
	double angle = ANGLE;
	if (obj_num %2 == 0)
		angle = -ANGLE;
	static int i = 0;
	static int j = -1;
	if (sphere->color.rgb[0] == 0)
	{
		return	 ;
	}
	if (i % 60 * sp_nbr == 0)
	{
		j = -j;
	}

	t_ray_vector point;
	point.axis[0] = -45;
	point.axis[1] = 0;
	point.axis[2] = -45;
	
	if (obj_num != 0)
	{
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


	if (j == 1 && obj_num != 0)
	{
		if (obj_num %2 == 0)
		{
			update_color(&sphere->color, -4);
			update_color(&sphere->color, -4);
		}
		else
		{
			update_color(&sphere->color, 4);
			update_color(&sphere->color, 4);
		}
	}
	else if (obj_num != 0)
	{
		if (obj_num %2 == 0)
		{
			update_color(&sphere->color, 4);
			update_color(&sphere->color, 4);
		}
		else
		{
			update_color(&sphere->color, -4);
			update_color(&sphere->color, -4);
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
	if (i % 60 * cyl_nbr == 0)
	{
		j = -j;
	}
	int axe[3];
	t_matrix_vector	trsf_matrix[MTX];
	t_matrix_vector applied_vect;
	double angle = ANGLE;
	if (obj_num %2 == 0)
		angle = -ANGLE;

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
	
	if (obj_num % 2 == 0)
	{
		if (j == 1)
		{
			update_color(&cyl->color, -4);
			update_color(&cyl->color, -4);
		}
		else
		{
			update_color(&cyl->color, 4);
			update_color(&cyl->color, 4);
		}
	}
	else
	{
		if (j == 1)
		{
			update_color(&cyl->color, 4);
			update_color(&cyl->color, 4);
		}
		else
		{
			update_color(&cyl->color, -4);
			update_color(&cyl->color, -4);
		}
	}
	i++;
}

void	video_rotate_cam(t_cam *cam)
{
	int axe[3];
	t_matrix_vector	trsf_matrix[MTX];
	t_matrix_vector applied_vect;
	double angle = ANGLE;

	t_matrix_vector point;
	point.axis[0] = 0;
	point.axis[1] = 0;
	point.axis[2] = 30;
	
	trsl_cam(cam, &point, point.axis);
	axe[0] = 0;
	axe[1] = 1;
	axe[2] = 0;
	rotate_cam(cam, angle, axe);
	symmetrize_vector(point.axis);
	// trsl_cam(cam, &point, point.axis);
}


void	video_rotate_light(t_spotlight *light)
{
	int axe[3];
	double angle = ANGLE;

	t_ray_vector point;
	point.axis[0] = -45;
	point.axis[1] = 0;
	point.axis[2] = -45;
	
	trsl_mesh(NULL, &light->bulb.origin_vect, point.axis);

	axe[0] = 0;
	axe[1] = 1;
	axe[2] = 0;
	rotate_mesh(&light->bulb.origin_vect, angle, axe);


	symmetrize_vector(point.axis);
	trsl_mesh(NULL, &light->bulb.origin_vect, point.axis);
	light->origin_vect = light->bulb.origin_vect;

}