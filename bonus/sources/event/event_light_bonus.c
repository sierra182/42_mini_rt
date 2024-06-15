#include "event_light_bonus.h"

/**========================================================================
 *                           EVENT_INTENSITY
 *========================================================================**/
void	event_intensity(int keycode, double *intensity)
{
	if (keycode == PLUS && *intensity <= 0.9)
		*intensity += 0.1;
	else if (keycode == MINUS && *intensity >= 0.1)
		*intensity -= 0.1;
}

/**========================================================================
 *                           HAS_BULB
 *========================================================================**/
static double	has_bulb(t_data *data, t_ray *ray)
{
	double	inter_bulb;
	int		i;

	i = -1;
	while (++i < data->sl_nbr)
	{
		inter_bulb = is_intersect_sphere(ray, &data->spotlights[i].bulb, NULL);
		if (inter_bulb && !is_behind_cam(inter_bulb))
		{
			data->event.actual_light = &data->spotlights[i];
			return (inter_bulb);
		}
	}
	return (0.0);
}

/**========================================================================
 *                           ACTUAL_LIGHT_HANDLE
 *========================================================================**/
void	actual_light_handle(t_data *data, int store_color,
	t_matrix_vector **origin_vect)
{
	t_color	*color;
	int		i;

	i = -1;
	if (store_color)
	{
		color = &data->event.actual_light->bulb.color;
		data->event.bulb_color_sav = *color ;
		i = -1;
		while (++i < AXIS)
			color->rgb[i] = 255 - color->rgb[i];
	}
	else if (data->event.actual_light)
		*origin_vect = &data->event.actual_light->origin_vect;
}

/**========================================================================
 *                      EVENT_SPOTLIGHT_LAUNCH_RAYS
 *========================================================================**/
void	event_spotlight_launch_rays(t_data *data, int x, int y)
{
	t_ray	ray;

	new_ray(&data->cam, &ray, x, y);
	if (has_bulb(data, &ray))
		actual_light_handle(data, 1, NULL);
}
