/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data_structs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:55:52 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:55:53 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_data_structs.h"

/**========================================================================
 *                           CREATE_DATA_STRUCTS
 *========================================================================**/
int	create_data_structs(t_data *data)
{
	data->spheres = (t_sphere *)malloc(sizeof(t_sphere) * data->sp_nbr);
	if (data->spheres == NULL)
		return (0);
	add_exit_struct(data->spheres, SP);
	data->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder) * data->cy_nbr);
	if (data->cylinders == NULL)
		return (0);
	add_exit_struct(data->cylinders, CY);
	data->planes = (t_plane *)malloc(sizeof(t_plane) * data->pl_nbr);
	if (data->planes == NULL)
		return (0);
	add_exit_struct(data->planes, PL);
	return (1);
}
