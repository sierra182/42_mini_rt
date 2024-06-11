#include "cam.h"

/**========================================================================
 *                           UPDATE_CAM
 *========================================================================**/
void	update_cam(t_cam *cam)
{
	cam->resol[0] = WIDTH;
	cam->resol[1] = HEIGHT;
	cam->fov_rad = cam->fov_deg * M_PI / 180.0;
	cam->scale = tan(cam->fov_rad * 0.5);
	if (cam->resol[1])
		cam->aspect = cam->resol[0] / cam->resol[1];
	if (cam->scale)
		cam->focal_len = cam->resol[0] / (2.0 * cam->scale);
}

/**========================================================================
 *                           CALCULATE_MISSING_VECTORS
 *========================================================================**/
void	calculate_missing_vectors(t_cam *cam)
{
	self_normalize_vector(cam->forward_vect.axis);
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
	self_normalize_vector(cam->right_vect.axis);
	cross_product(&cam->forward_vect, &cam->right_vect, &cam->up_vect);
	self_normalize_vector(cam->up_vect.axis);
}

/**========================================================================
 *                           POST_INIT_CAM
 *========================================================================**/
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
