/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_funcs_2_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:34:08 by svidot            #+#    #+#             */
/*   Updated: 2024/06/28 07:17:13 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_struct_funcs_2_bonus.h"

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
	data->spheres[i].checkerboard = 0;
	data->spheres[i].reflexion_coef = tab[7];
	handle_uv_modif_params(tab[8], data, i);
	data->spheres[i].which_t = 0;
	data->spheres[i].t1 = 0.0;
	data->spheres[i].t2 = 0.0;
	data->spheres[i].rotation_angle_x = 0.0;
	data->spheres[i].rotation_angle_y = 0.0;
	data->spheres[i].bump_flag = 0;
	i++;
}

/**========================================================================
 *                           HANDLE_UV_MODIF_PARAMS
 *========================================================================**/
void	handle_uv_modif_params(double nbr, t_data *data, int i)
{
	if ((int)nbr == -42)
	{
		data->spheres[i].checkerboard = 1;
		data->spheres[i].bump_map_nbr = -1;
	}
	else if ((int)nbr != 1024)
	{
		data->spheres[i].bump_map_path = get_bmpath(data, (int)nbr);
		data->spheres[i].bump_map_nbr = i;
		data->spheres[i].checkerboard = 0;
		get_texture(data, i);
	}
	else
	{
		data->spheres[i].checkerboard = 0;
		data->spheres[i].bump_map_nbr = -1;
	}
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
	data->cylinders[i].reflexion_coef = tab[11];
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
	data->planes[i].reflexion_coef = tab[9];
	if (tab[9] == -42)
		data->planes[i].checkerboard = 1;
	else if ((int)tab[9] != 1024)
	{
		data->planes[i].checkerboard = 0;
		data->planes[i].bump_map_path = get_bmpath(data, (int)tab[9]);
	}
	else
		data->planes[i].checkerboard = 0;
	i++;
}

/**========================================================================
 *                           FILL_STRUCT_TR
 *========================================================================**/
void	fill_struct_tr(t_data *data, double tab[])
{
	static int	i = 0;

	data->triangles[i].point_a.axis[0] = tab[0];
	data->triangles[i].point_a.axis[1] = tab[1];
	data->triangles[i].point_a.axis[2] = tab[2];
	data->triangles[i].point_a.axis[3] = 1;
	data->triangles[i].point_b.axis[0] = tab[3];
	data->triangles[i].point_b.axis[1] = tab[4];
	data->triangles[i].point_b.axis[2] = tab[5];
	data->triangles[i].point_b.axis[3] = 1;
	data->triangles[i].point_c.axis[0] = tab[6];
	data->triangles[i].point_c.axis[1] = tab[7];
	data->triangles[i].point_c.axis[2] = tab[8];
	data->triangles[i].point_c.axis[3] = 1;
	data->triangles[i].color.rgb[0] = tab[9];
	data->triangles[i].color.rgb[1] = tab[10];
	data->triangles[i].color.rgb[2] = tab[11];
	data->triangles[i].reflexion_coef = tab[12];
	i++;
}
