/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:54:11 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:54:12 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_reset.h"

/**========================================================================
 *                           RESET
 *========================================================================**/
void	reset(t_data *data)
{
	t_reset_tmps	tmps;

	tmps.planes = data->planes;
	tmps.spheres = data->spheres;
	tmps.cylinders = data->cylinders;
	tmps.data_cpy = data->data_cpy;
	tmps.planes_cpy = data->data_cpy->planes;
	tmps.spheres_cpy = data->data_cpy->spheres;
	tmps.cylinders_cpy = data->data_cpy->cylinders;
	*data = *data->data_cpy;
	data->planes = tmps.planes;
	data->spheres = tmps.spheres;
	data->cylinders = tmps.cylinders;
	data->data_cpy = tmps.data_cpy;
	ft_memcpy(data->planes, tmps.planes_cpy, data->pl_nbr
		* sizeof(t_plane));
	ft_memcpy(data->spheres, tmps.spheres_cpy, data->sp_nbr
		* sizeof(t_sphere));
	ft_memcpy(data->cylinders, tmps.cylinders_cpy, data->cy_nbr
		* sizeof(t_cylinder));
}

/**========================================================================
 *                           RESET_CAM
 *========================================================================**/
void	reset_cam(t_data *data)
{
	data->cam.forward_vect.axis[1] = 0;
	calculate_missing_vectors(&data->cam);
}
