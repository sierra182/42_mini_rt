#include "mouse_events_bonus.h"

/**========================================================================
 *                           MOUSE_EVENT
 *========================================================================**/
int	mouse_event(int button, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	data->refresh = 1;
	if (button == 1)
	{
		if (x >= 0 && x < 100 && y >= 0 && y < 100)
			return (data->event.legend = (data->event.legend + 1) % 2, 0);
		if (data->event.actual_mode == E_MESH)
			event_launch_rays(data, x, y);
		if (data->event.actual_mode == E_SPOTL)
			event_spotlight_launch_rays(data, x, y);
		return (0);
	}
	else if (button == 5 && data->cam.fov_deg < 180)
		data->cam.fov_deg++;
	else if (button == 4 && data->cam.fov_deg > 0)
		data->cam.fov_deg--;
	update_cam(&data->cam);
	return (0);
}

/**========================================================================
 *                           MOUSE_RELEASE
 *========================================================================**/
int	mouse_release(int button, int x, int y, void *param)
{
	t_data	*data;

	(void) button;
	(void) x;
	(void) y;
	data = (t_data *) param;
	if (data->event.actual_mesh.ref)
	{
		data->refresh = 1;
		if (data->event.actual_mesh.type == O_SP)
		{
			((t_sphere *) data->event.actual_mesh.ref)->color
				= data->event.color_sav;
			((t_sphere *) data->event.actual_mesh.ref)->bump_flag = 0;
		}
		else if (data->event.actual_mesh.type == O_PL)
			((t_plane *) data->event.actual_mesh.ref)->color
				= data->event.color_sav;
		else if (data->event.actual_mesh.type == O_CY)
			((t_cylinder *) data->event.actual_mesh.ref)->color
				= data->event.color_sav;
	}
	if (data->event.actual_light)
	{
		data->refresh = 1;
		data->event.actual_light->bulb.color = data->event.bulb_color_sav;
	}
	return (0);
}

/**========================================================================
 *                           KEY_UP_EVENT
 *========================================================================**/
void	key_up_event(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)((void **) param)[1];
	if (keycode == CTRL || keycode == CTRL_2)
		data->event.ctrl_ispressed = 0;
}
