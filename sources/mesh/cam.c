# include <math.h>
# include "x_mini_struct.h"
# include "x_matrix.h"
# include "x_linear_algebra.h"

void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);

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

void	calculate_missing_vectors(t_cam *cam)
{
	normalize_vector(cam->forward_vect.axis);
	cam->up_vect.axis[0] = 0;
	cam->up_vect.axis[1] = 1;
	cam->up_vect.axis[2] = 0;
	cross_product(&cam->up_vect, &cam->forward_vect, &cam->right_vect);
	if (are_collinear_vectors(&cam->right_vect, 1e-3))
	{
		cam->up_vect.axis[0] = -1;
		cam->up_vect.axis[1] = 0;
		cam->up_vect.axis[2] = 0;
		cross_product(&cam->up_vect, &cam->forward_vect, &cam->right_vect);
	}
	normalize_vector(cam->right_vect.axis);
	cross_product(&cam->forward_vect, &cam->right_vect, &cam->up_vect);
	normalize_vector(cam->up_vect.axis);
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

static void	cast_matrix_cam(t_cam *cam, t_matrix_vector mult_matrix[MTX])
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

void	trsl_cam(t_cam *cam, t_matrix_vector *vect, double values[])
{
	t_matrix_vector scaled_vect;
	double			value;

	if (values[1])
		return (trsl_mesh(NULL, &cam->origin_vect, values));
	if (values[0])
		scale_vector(cam->right_vect.axis, values[0], scaled_vect.axis);
	else if (values[2])
		scale_vector(cam->forward_vect.axis, values[2], scaled_vect.axis);
	add_vector(scaled_vect.axis, cam->origin_vect.axis, cam->origin_vect.axis);
}

void	trsl_about_cam(t_cam *cam, t_matrix_vector *vect, double values[])
{
	t_matrix_vector scaled_vect;
	double			value;
	
	if (values[1])
		return (trsl_mesh(NULL, vect, values));
	if (values[0])
		scale_vector(cam->right_vect.axis, values[0], scaled_vect.axis);
	else if (values[2])
		scale_vector(cam->forward_vect.axis, values[2], scaled_vect.axis);
	add_vector(scaled_vect.axis, vect->axis, vect->axis);
}
