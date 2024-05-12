#include "fill_struct_funcs.h"

void	fill_struct_a(t_data *data, double tab[])
{
	data->ambiant_light.intensity = tab[0];
	data->ambiant_light.color.rgb[0] = tab[1];
	data->ambiant_light.color.rgb[1] = tab[2];
	data->ambiant_light.color.rgb[2] = tab[3];
}

void	fill_struct_c(t_data *data, double tab[])
{
	data->cam.origin_vect.axis[0] = tab[0];
	data->cam.origin_vect.axis[1] = tab[1];
	data->cam.origin_vect.axis[2] = tab[2];
	data->cam.forward_vect.axis[0] = tab[3];
	data->cam.forward_vect.axis[1] = tab[4];
	data->cam.forward_vect.axis[2] = tab[5];
	data->cam.fov_deg = tab[6];
}

void	fill_struct_l(t_data *data, double tab[])
{
	data->spotlight.origin_vect.axis[0] = tab[0];
	data->spotlight.origin_vect.axis[1] = tab[1];
	data->spotlight.origin_vect.axis[2] = tab[2];
	data->spotlight.origin_vect.axis[3] = 1;
	data->spotlight.intensity = tab[3];
	data->spotlight.bulb.color.rgb[0] = 255;
	data->spotlight.bulb.color.rgb[1] = 255;
	data->spotlight.bulb.color.rgb[2] = 255;
	data->spotlight.bulb.diameter = 1;
	data->spotlight.bulb.square_radius = (data->spotlight.bulb.diameter / 2)
		* (data->spotlight.bulb.diameter / 2);
	data->spotlight.bulb.origin_vect = data->spotlight.origin_vect;
}
