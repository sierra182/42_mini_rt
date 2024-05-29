#include "x_mini_struct.h"
#include "mlx.h"

void	reset(t_data *data);
void	reset_cam(t_data *data);
void	trsl_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	actual_mesh_handle(t_data *data, t_obj *mesh,
			t_matrix_vector **origin_vect, t_matrix_vector **dir_vect);
void	trsl_about_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	make_rt_file(t_data *data);
void	video_rotate_element(t_sphere *sphere);
void	chang_mesh_size(t_data *data, int keycode);
void	event_intensity(int keycode, double *intensity);
void	cam_event_rotate(int keycode, t_cam *cam);
void	event_rotate(int keycode, t_matrix_vector *vector);
void	event_translate(int keycode,
			void (*trsl_mesh)(t_cam *cam, t_matrix_vector *vect,
			double values[]), t_cam *cam, t_matrix_vector *vect);

void	meta_keycode(int keycode, t_data *data)
{
	int	i;

	if (keycode == MAKE_RT_FILE)
		make_rt_file(data);
	if (keycode == VIDEO_NEXT_FRAME)
	{
		i = 0;
		while (i < data->sp_nbr)
			video_rotate_element(&data->spheres[i++]);
	}
}
/**========================================================================
 *                           KEY_EVENT
 *========================================================================**/
int	key_event(int keycode, void *param)
{
	t_mlx						*mlx;
	t_data						*data;
	t_matrix_vector				*rotate_vect;
	t_matrix_vector				*transl_vect;

	mlx = (t_mlx *)((void **) param)[0];
	data = (t_data *)((void **) param)[1];
	rotate_vect = NULL;
	transl_vect = NULL;
	data->refresh = 1;
	// printf("keycode: %d\n", keycode);
	if (keycode == ESC)
		mlx_loop_end(mlx->connect);
	if (keycode == RST)
		reset(data);
	if (keycode == RST_CM)
		reset_cam(data);
	if (keycode == MESH)
		data->event.type_mesh = E_MESH;
	if (keycode == CAM)
		data->event.type_mesh = E_CAM;
	if (keycode == LIGHT)
		data->event.type_mesh = E_SPOTL;
	if (keycode == AMBL)
		data->event.type_mesh = E_AMBL;
	if (keycode == CTRL || keycode == CTRL_2)
		data->event.ctrl_ispressed = 1;
	if (data->event.type_mesh == E_CAM)
	{
		event_translate(keycode, trsl_cam, &data->cam, NULL);
		cam_event_rotate(keycode, &data->cam);
	}
	if (data->event.type_mesh == E_SPOTL)
		event_translate(keycode, trsl_about_cam, &data->cam,
			&data->spotlight.origin_vect);
	if (data->event.type_mesh == E_MESH)
	{
		actual_mesh_handle(data, NULL, &transl_vect, &rotate_vect);
		if (transl_vect)
			event_translate(keycode, trsl_about_cam, &data->cam, transl_vect);
		if (rotate_vect)
			event_rotate(keycode, rotate_vect);
	}
	if (data->event.type_mesh == E_MESH && (keycode == PLUS
			|| keycode == MINUS))
		chang_mesh_size(data, keycode);
	if (data->event.type_mesh == E_SPOTL)
	{
		data->spotlight.bulb.origin_vect = data->spotlight.origin_vect;
		event_intensity(keycode, &data->spotlight.intensity);
	}
	if (data->event.type_mesh == E_AMBL)
		event_intensity(keycode, &data->ambiant_light.intensity);
	meta_keycode(keycode, data);
	return (0);
}
