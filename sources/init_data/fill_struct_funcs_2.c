/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_funcs_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:55:56 by svidot            #+#    #+#             */
/*   Updated: 2024/06/28 07:39:12 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_struct_funcs_2.h"

/**========================================================================
 *                           FILL_STRUCT_SP
 *========================================================================**/
void	fill_struct_sp(t_data *data, double tab[])
{
	static int	i = 0;

	data->spheres[i].origin_vect.axis[0] = tab[0];
	data->spheres[i].origin_vect.axis[1] = tab[1];
	data->spheres[i].origin_vect.axis[2] = tab[2];
	data->spheres[i].origin_vect.axis[3] = 1;
	data->spheres[i].diameter = tab[3];
	data->spheres[i].radius = data->spheres[i].diameter * 0.5;
	data->spheres[i].square_radius = data->spheres[i].radius
		* data->spheres[i].radius;
	data->spheres[i].color.rgb[0] = tab[4];
	data->spheres[i].color.rgb[1] = tab[5];
	data->spheres[i].color.rgb[2] = tab[6];
	data->spheres[i].which_t = 0;
	data->spheres[i].t1 = 0.0;
	data->spheres[i].t2 = 0.0;
	i++;
}

/**========================================================================
 *                           FILL_STRUCT_CY
 *========================================================================**/
void	fill_struct_cy(t_data *data, double tab[])
{
	static int	i = 0;

	data->cylinders[i].origin_vect.axis[0] = tab[0];
	data->cylinders[i].origin_vect.axis[1] = tab[1];
	data->cylinders[i].origin_vect.axis[2] = tab[2];
	data->cylinders[i].origin_vect.axis[3] = 1;
	data->cylinders[i].axis_vect.axis[0] = tab[3];
	data->cylinders[i].axis_vect.axis[1] = tab[4];
	data->cylinders[i].axis_vect.axis[2] = tab[5];
	data->cylinders[i].axis_vect.axis[3] = 1;
	data->cylinders[i].diameter = tab[6];
	data->cylinders[i].radius = data->cylinders[i].diameter * 0.5;
	data->cylinders[i].square_radius = data->cylinders[i].radius
		* data->cylinders[i].radius;
	data->cylinders[i].height = tab[7];
	data->cylinders[i].color.rgb[0] = tab[8];
	data->cylinders[i].color.rgb[1] = tab[9];
	data->cylinders[i].color.rgb[2] = tab[10];
	data->cylinders[i].which_t = 0;
	data->cylinders[i].t1 = 0.0;
	data->cylinders[i].t2 = 0.0;
	i++;
}

/**========================================================================
 *                           FILL_STRUCT_PL
 *========================================================================**/
void	fill_struct_pl(t_data *data, double tab[])
{
	static int	i = 0;

	data->planes[i].origin_vect.axis[0] = tab[0];
	data->planes[i].origin_vect.axis[1] = tab[1];
	data->planes[i].origin_vect.axis[2] = tab[2];
	data->planes[i].origin_vect.axis[3] = 1;
	data->planes[i].norm_vect.axis[0] = tab[3];
	data->planes[i].norm_vect.axis[1] = tab[4];
	data->planes[i].norm_vect.axis[2] = tab[5];
	data->planes[i].norm_vect.axis[3] = 1;
	data->planes[i].color.rgb[0] = tab[6];
	data->planes[i].color.rgb[1] = tab[7];
	data->planes[i].color.rgb[2] = tab[8];
	i++;
}
