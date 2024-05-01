#define PI 3.14159265358979323846
#include <math.h>
#include "x_mini_struct.h"

void	normalize_vector(t_vector *vector);
void	product_vector(t_vector *a, t_vector *b, t_vector *product_vect);
int		are_collinear_vectors(t_vector *pdct_vect, double precision);

static void	calculate_missing_vectors(t_cam *cam)
{
	normalize_vector(&cam->forward_vect);
	cam->up_vect.axis[0] = 0;
	cam->up_vect.axis[1] = 1;
	cam->up_vect.axis[2] = 0;
	product_vector(&cam->up_vect, &cam->forward_vect, &cam->right_vect);
	if (are_collinear_vectors(&cam->right_vect, 1e-3))
	{
		cam->up_vect.axis[0] = -1;
		cam->up_vect.axis[1] = 0;
		cam->up_vect.axis[2] = 0;
		product_vector(&cam->up_vect, &cam->forward_vect, &cam->right_vect);
	}
	normalize_vector(&cam->right_vect);
	product_vector(&cam->forward_vect, &cam->right_vect, &cam->up_vect);
	normalize_vector(&cam->up_vect);
}

void	update_cam(t_cam *cam)
{
	calculate_missing_vectors(cam);
	cam->resol[0] = WIDTH;
	cam->resol[1] = HEIGHT;
	cam->fov = cam->fov * PI / 180.0;
	cam->scale = tan(cam->fov / 2.0);
	if (cam->resol[1])
		cam->aspect = cam->resol[0] / cam->resol[1];
	if (cam->scale)
		cam->focal_len = cam->resol[0] / (2.0 * cam->scale);
}
