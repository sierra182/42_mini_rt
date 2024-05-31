#include "x_mini_struct.h"
#include "mlx.h"

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);
void	rotate_cam(t_cam *cam, double angle, int axe[]);
void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);
void	reset(t_data *data);
void	reset_cam(t_data *data);
void	trsl_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	actual_mesh_handle(t_data *data, t_obj *mesh,
			t_matrix_vector **origin_vect, t_matrix_vector **dir_vect);
void	trsl_about_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	make_rt_file(t_data *data);
void	video_rotate_element(t_sphere *sphere, int obj_nbr);
void	chang_mesh_size(t_data *data, int keycode);
void	event_intensity(int keycode, double *intensity);

/**========================================================================
 *                           CAM_EVENT_ROTATE
 *========================================================================**/
void	cam_event_rotate(int keycode, t_cam *cam)
{
	double	r;

	r = 1.0;
	if (keycode == R_LFT)
		rotate_cam(cam, r, (int []){0, 1, 0});
	else if (keycode == R_RGHT)
		rotate_cam(cam, -r, (int []){0, 1, 0});
	else if (keycode == R_UP)
		rotate_cam(cam, r, (int []){1, 0, 0});
	else if (keycode == R_DWN)
		rotate_cam(cam, -r, (int []){1, 0, 0});
	else if (keycode == S_LFT)
		rotate_cam(cam, r, (int []){0, 0, 1});
	else if (keycode == S_RGHT)
		rotate_cam(cam, -r, (int []){0, 0, 1});
}

/**========================================================================
 *                           EVENT_ROTATE
 *========================================================================**/
void	event_rotate(int keycode, t_matrix_vector *vector)
{
	double	r;

	r = 1.0;
	if (keycode == R_LFT)
		rotate_mesh(vector, r, (int []){1, 0, 0});
	else if (keycode == R_RGHT)
		rotate_mesh(vector, -r, (int []){1, 0, 0});
	else if (keycode == R_UP)
		rotate_mesh(vector, r, (int []){0, 1, 0});
	else if (keycode == R_DWN)
		rotate_mesh(vector, -r, (int []){0, 1, 0});
	else if (keycode == S_LFT)
		rotate_mesh(vector, r, (int []){0, 0, 1});
	else if (keycode == S_RGHT)
		rotate_mesh(vector, -r, (int []){0, 0, 1});
}

/**========================================================================
 *                           EVENT_TRANSLATE
 *========================================================================**/
void	event_translate(int keycode,
	void (*trsl_mesh)(t_cam *cam, t_matrix_vector *vect, double values[]),
		t_cam *cam, t_matrix_vector *vect)
{
	double	t;

	t = 1;
	if (keycode == UP)
		trsl_mesh(cam, vect, (double []){0.0, t, 0.0});
	else if (keycode == DWN)
		trsl_mesh(cam, vect, (double []){0.0, -t, 0.0});
	else if (keycode == LFT)
		trsl_mesh(cam, vect, (double []){t, 0.0, 0.0});
	else if (keycode == RGHT)
		trsl_mesh(cam, vect, (double []){-t, 0.0, 0.0});
	else if (keycode == FWRD)
		trsl_mesh(cam, vect, (double []){0.0, 0.0, t});
	else if (keycode == BACK)
		trsl_mesh(cam, vect, (double []){0.0, 0.0, -t});
}
