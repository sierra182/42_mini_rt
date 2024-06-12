#include "fill_struct_funcs_bonus.h"

/**========================================================================
 *                           FILL_STRUCT_A
 *========================================================================**/
void	fill_struct_a(t_data *data, double tab[])
{
	data->ambiant_light.intensity = tab[0];
	data->ambiant_light.color.rgb[0] = tab[1];
	data->ambiant_light.color.rgb[1] = tab[2];
	data->ambiant_light.color.rgb[2] = tab[3];
}

/**========================================================================
 *                           FILL_STRUCT_C
 *========================================================================**/
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
