#include "key_event_bonus.h"

void	event_rotate_sphere(t_data *data, int keycode, t_matrix_vector *vector);

/**========================================================================
 *                           KEY_CODE_FUNCS
 *========================================================================**/
void	key_code_funcs(int keycode, t_data *data, t_mlx *mlx)
{
	if (keycode == ESC)
		mlx_loop_end(mlx->connect);
	if (keycode == ANT)
		data->event.antia = 1;
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
	t_matrix_vector	*transl_vect;

	transl_vect = NULL;
	if (data->event.actual_mode == E_CAM)
	{
		event_translate(keycode, trsl_cam, &data->cam, NULL);
		cam_event_rotate(keycode, &data->cam);
	}
	if (data->event.actual_mode == E_SPOTL)
	{
		actual_light_handle(data, 0, &transl_vect);
		if (transl_vect)
		{
			event_translate(keycode, trsl_about_cam, &data->cam, transl_vect);
			data->event.actual_light->bulb.origin_vect
				= data->event.actual_light->origin_vect;
		}
	}
}

/**========================================================================
 *                           DATA_EVENT_FUNCS_2
 *========================================================================**/
void	data_event_funcs_2(t_data *data, int keycode, t_mlx *mlx)
{
	t_matrix_vector	*rotate_vect;
	t_matrix_vector	*transl_vect;

	rotate_vect = NULL;
	transl_vect = NULL;
	if (data->event.actual_mode == E_MESH)
	{
		actual_mesh_handle(data, NULL, &transl_vect, &rotate_vect);
		if (transl_vect)
			event_translate(keycode, trsl_about_cam, &data->cam, transl_vect);
		if (rotate_vect)
			event_rotate(data, keycode, rotate_vect);
		if (data->event.actual_mesh.type == O_SP)
			event_rotate_sphere(data, keycode, rotate_vect);
	}
	if (data->event.actual_mode == E_MESH && (keycode == PLUS
			|| keycode == MINUS))
		chang_mesh_size(data, keycode);
	if (data->event.actual_mode == E_AMBL)
		event_intensity(keycode, &data->ambiant_light.intensity);
	meta_keycode(keycode, data, mlx);
	if (data->event.actual_mode == E_SPOTL && data->event.actual_light)
		event_intensity(keycode, &data->event.actual_light->intensity);
}

/**========================================================================
 *                           KEY_EVENT
 *========================================================================**/
int	key_event(int keycode, void *param)
{
	t_mlx	*mlx;
	t_data	*data;

	mlx = (t_mlx *)((void **) param)[0];
	data = (t_data *)((void **) param)[1];
	data->refresh = 1;
	key_code_funcs(keycode, data, mlx);
	data_event_funcs_1(data, keycode);
	data_event_funcs_2(data, keycode, mlx);
	return (0);
}
