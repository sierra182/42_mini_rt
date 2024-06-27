/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_funcs_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:34:17 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 15:34:18 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**========================================================================
 *                           FILL_STRUCT_L
 *========================================================================**/
void	fill_struct_l(t_data *data, double tab[])
{
	static int	i = 0;

	data->spotlights[i].origin_vect.axis[0] = tab[0];
	data->spotlights[i].origin_vect.axis[1] = tab[1];
	data->spotlights[i].origin_vect.axis[2] = tab[2];
	data->spotlights[i].origin_vect.axis[3] = 1;
	data->spotlights[i].intensity = tab[3];
	data->spotlights[i].color.rgb[0] = tab[4];
	data->spotlights[i].color.rgb[1] = tab[5];
	data->spotlights[i].color.rgb[2] = tab[6];
	data->spotlights[i].bulb.color = data->spotlights[i].color;
	data->spotlights[i].bulb.diameter = 0;
	data->spotlights[i].bulb.radius = data->spotlights[i].bulb.diameter * 0.5;
	data->spotlights[i].bulb.square_radius = data->spotlights[i].bulb.radius
		* data->spotlights[i].bulb.radius;
	data->spotlights[i].bulb.origin_vect = data->spotlights[i].origin_vect;
	i++;
}
