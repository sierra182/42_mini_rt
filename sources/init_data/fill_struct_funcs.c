/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:56:23 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:56:24 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_struct_funcs.h"

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

/**========================================================================
 *                           FILL_STRUCT_L
 *========================================================================**/
void	fill_struct_l(t_data *data, double tab[])
{
	data->spotlight.origin_vect.axis[0] = tab[0];
	data->spotlight.origin_vect.axis[1] = tab[1];
	data->spotlight.origin_vect.axis[2] = tab[2];
	data->spotlight.origin_vect.axis[3] = 1;
	data->spotlight.intensity = tab[3];
	data->spotlight.color.rgb[0] = tab[4];
	data->spotlight.color.rgb[1] = tab[5];
	data->spotlight.color.rgb[2] = tab[6];
	data->spotlight.bulb.color = data->spotlight.color;
	data->spotlight.bulb.diameter = 1;
	data->spotlight.bulb.radius = data->spotlight.bulb.diameter * 0.5;
	data->spotlight.bulb.square_radius = data->spotlight.bulb.radius
		* data->spotlight.bulb.radius;
	data->spotlight.bulb.origin_vect = data->spotlight.origin_vect;
}
