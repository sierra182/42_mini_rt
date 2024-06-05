#include "se_mini_struct.h"
#include "mlx.h"

void	reset(t_data *data);
void	reset_cam(t_data *data);
void	trsl_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	actual_mesh_handle(t_data *data, t_obj *mesh,
			t_matrix_vector **origin_vect, t_matrix_vector **dir_vect);
void	trsl_about_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	make_rt_file(t_data *data);
void	video_rotate_spheres(t_sphere *sphere, int obj_nbr);
void	chang_mesh_size(t_data *data, int keycode);
void	event_intensity(int keycode, double *intensity);
void	cam_event_rotate(int keycode, t_cam *cam);
void	event_rotate(int keycode, t_matrix_vector *vector);
void	event_translate(int keycode,
			void (*trsl_mesh)(t_cam *cam, t_matrix_vector *vect,
				double values[]), t_cam *cam, t_matrix_vector *vect);
void	meta_keycode(int keycode, t_data *data, t_mlx *mlx);

/**========================================================================
 *                           KEY_CODE_FUNCS
 *========================================================================**/
void	key_code_funcs(int keycode, t_data *data, t_mlx *mlx)
{
	if (keycode == ESC)
		mlx_loop_end(mlx->connect);
	if (keycode == RST)
		reset(data);
	if (keycode == RST_CM)
		reset_cam(data);
	if (keycode == MESH)
		data->event.actual_mode = E_MESH;
	if (keycode == CAM)
		data->event.actual_mode = E_CAM;
	if (keycode == LIGHT)
		data->event.actual_mode = E_SPOTL;
	if (keycode == AMBL)
		data->event.actual_mode = E_AMBL;
	if (keycode == CTRL || keycode == CTRL_2)
		data->event.ctrl_ispressed = 1;
}

/**========================================================================
 *                           DATA_EVENT_FUNCS_1
 *========================================================================**/
void	data_event_funcs_1(t_data *data, int keycode)
{
	t_matrix_vector				*rotate_vect;
	t_matrix_vector				*transl_vect;

	rotate_vect = NULL;
	transl_vect = NULL;
	if (data->event.actual_mode == E_CAM)
	{
		event_translate(keycode, trsl_cam, &data->cam, NULL);
		cam_event_rotate(keycode, &data->cam);
	}
	if (data->event.actual_mode == E_SPOTL)
		event_translate(keycode, trsl_about_cam, &data->cam,
			&data->spotlight.origin_vect);
	if (data->event.actual_mode == E_MESH)
	{
		actual_mesh_handle(data, NULL, &transl_vect, &rotate_vect);
		if (transl_vect)
			event_translate(keycode, trsl_about_cam, &data->cam, transl_vect);
		if (rotate_vect)
			event_rotate(keycode, rotate_vect);
	}
	if (data->event.actual_mode == E_MESH && (keycode == PLUS
			|| keycode == MINUS))
		chang_mesh_size(data, keycode);
}

/**========================================================================
 *                           DATA_EVENT_FUNCS_2
 *========================================================================**/
void	data_event_funcs_2(t_data *data, int keycode, t_mlx *mlx)
{
	if (data->event.actual_mode == E_AMBL)
		event_intensity(keycode, &data->ambiant_light.intensity);
	meta_keycode(keycode, data, mlx);
	if (data->event.actual_mode == E_SPOTL)
	{
		data->spotlight.bulb.origin_vect = data->spotlight.origin_vect;
		event_intensity(keycode, &data->spotlight.intensity);
	}
}

/**========================================================================
 *                           KEY_EVENT
 *========================================================================**/
int	key_event(int keycode, void *param)
{
	t_mlx						*mlx;
	t_data						*data;

	mlx = (t_mlx *)((void **) param)[0];
	data = (t_data *)((void **) param)[1];
	data->refresh = 1;
	// printf("keycode: %d\n", keycode);
	key_code_funcs(keycode, data, mlx);
	data_event_funcs_1(data, keycode);
	data_event_funcs_2(data, keycode, mlx);
	return (0);
}
