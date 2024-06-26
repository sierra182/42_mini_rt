/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_store_shapes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:55:02 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:55:03 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_store_shapes.h"

/**========================================================================
 *                           STORE_AND_FREE_SPHERES
 *========================================================================**/
void	store_and_free_spheres(t_exit *exit, void *spheres)
{
	if (exit && spheres)
		exit->spheres = (t_sphere *) spheres;
	else if (exit && exit->spheres)
	{
		free(exit->spheres);
		exit->spheres = NULL;
	}
}

/**========================================================================
 *                           STORE_AND_FREE_CYLINDERS
 *========================================================================**/
void	store_and_free_cylinders(t_exit *exit, void *cylinders)
{
	if (exit && cylinders)
		exit->cylinders = (t_cylinder *) cylinders;
	else if (exit && exit->cylinders)
	{
		free(exit->cylinders);
		exit->cylinders = NULL;
	}
}

/**========================================================================
 *                           STORE_AND_FREE_PLANES
 *========================================================================**/
void	store_and_free_planes(t_exit *exit, void *planes)
{
	if (exit && planes)
		exit->planes = (t_plane *) planes;
	else if (exit && exit->planes)
	{
		free(exit->planes);
		exit->planes = NULL;
	}
}
