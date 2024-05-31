#ifndef X_CAMERA_H
# define X_CAMERA_H

typedef struct s_cam
{
	double			fov_deg;
	double			fov_rad;
	double			focal_len;
	double			scale;
	double			aspect;
	double			resol[2];
	t_matrix_vector	*cam_matrix[MTX];
	t_matrix_vector	right_vect;
	t_matrix_vector	up_vect;
	t_matrix_vector	forward_vect;
	t_matrix_vector	origin_vect;
}	t_cam;

#endif