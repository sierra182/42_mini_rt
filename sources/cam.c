#include <math.h>
#include "x_mini_struct.h"

void	normalize_vector(t_matrix_vector *vector);
void	product_vector(t_matrix_vector *a, t_matrix_vector *b, t_matrix_vector *product_vect);
int		are_collinear_vectors(t_matrix_vector *pdct_vect, double precision);
void	init_matrix(t_matrix_vector matrix[]);
void	apply_matrix(t_matrix_vector matrix[], t_matrix_vector *vector, t_matrix_vector *applied_vect);
void	set_matrix_translate(t_matrix_vector matrix[], double trans[]);
void	set_matrix_rotation(t_matrix_vector matrix[], double angle, int axe[]);
void	multiply_matrix(t_matrix_vector a[], t_matrix_vector b[], t_matrix_vector mult_mat[]);

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

void	post_init_cam(t_cam *cam)
{
	calculate_missing_vectors(cam);
	cam->right_vect.axis[3] = 0;
	cam->up_vect.axis[3] = 0;
	cam->forward_vect.axis[3] = 0;
	cam->origin_vect.axis[3] = 1;
	cam->cam_matrix[0] = &cam->right_vect;
	cam->cam_matrix[1] = &cam->up_vect;
	cam->cam_matrix[2] = &cam->forward_vect;
	cam->cam_matrix[3] = &cam->origin_vect;
}

void	update_cam(t_cam *cam)
{	
	cam->resol[0] = WIDTH;
	cam->resol[1] = HEIGHT;
	cam->fov_rad = cam->fov_deg * M_PI / 180.0;
	cam->scale = tan(cam->fov_rad / 2.0);
	if (cam->resol[1])
		cam->aspect = cam->resol[0] / cam->resol[1];
	if (cam->scale)
		cam->focal_len = cam->resol[0] / (2.0 * cam->scale);
}

void	trsl_vector(t_matrix_vector *vect, double values[])
{
	t_matrix_vector applied_vect;
	t_matrix_vector	trsf_matrix[MTX];

	init_matrix(trsf_matrix);
	set_matrix_translate(trsf_matrix, values);
	apply_matrix(trsf_matrix, vect, &applied_vect);
	*vect = applied_vect;
	//printf("x: %f, y: %f, z:%f\n", vect->axis[0], vect->axis[1], vect->axis[2]);
}
void	cast_matrix_cam(t_cam *cam, t_matrix_vector mult_matrix[MTX])
{
	int	i;

	i = -1;
	while (++i < MTX)	
		*cam->cam_matrix[i] = mult_matrix[i];
}
void	rotate_cam(t_cam *cam, double angle, int axe[])
{
	t_matrix_vector mult_matrix[MTX];
	t_matrix_vector	trsf_matrix[MTX];

	init_matrix(trsf_matrix);
	set_matrix_rotation(trsf_matrix, angle, axe);
	multiply_matrix(trsf_matrix, *cam->cam_matrix, mult_matrix);
	cast_matrix_cam(cam, mult_matrix);
}