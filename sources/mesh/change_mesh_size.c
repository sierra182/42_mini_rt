/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_mesh_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:59:09 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:59:10 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "change_mesh_size.h"

/**========================================================================
 *							HANDLE_PLUS_KEY
========================================================================**/
void	handle_plus_key(t_data *data)
{
	t_event		*mesh;
	t_sphere	*sphere;
	t_cylinder	*cyl;
	t_obj		obj;

	mesh = &data->event;
	obj = mesh->actual_mesh;
	sphere = ((t_sphere *)obj.ref);
	cyl = ((t_cylinder *)obj.ref);
	if (obj.type == O_SP)
	{
		sphere->diameter += 1;
		sphere->radius = sphere->diameter * 0.5;
		sphere->square_radius = pow(sphere->radius, 2);
	}
	else if (obj.type == O_CY && mesh->ctrl_ispressed)
		cyl->height += 1;
	else if (obj.type == O_CY && !mesh->ctrl_ispressed)
	{
		cyl->diameter += 1;
		cyl->radius = cyl->diameter * 0.5;
		cyl->square_radius = pow(cyl->radius, 2);
	}
}

/**========================================================================
 * 							HANDLE_MINUS_KEY
========================================================================**/
void	handle_minus_key(t_data *data)
{
	t_event		*mesh;
	t_sphere	*sphere;
	t_cylinder	*cyl;
	t_obj		obj;

	mesh = &data->event;
	obj = mesh->actual_mesh;
	sphere = ((t_sphere *)obj.ref);
	cyl = ((t_cylinder *)obj.ref);
	if (obj.type == O_SP && sphere->diameter > 1)
	{
		sphere->diameter -= 1;
		sphere->radius = sphere->diameter * 0.5;
		sphere->square_radius = pow(sphere->radius, 2);
	}
	else if (obj.type == O_CY && mesh->ctrl_ispressed && cyl->height > 1)
		cyl->height -= 1;
	else if (obj.type == O_CY && !mesh->ctrl_ispressed && cyl->diameter > 1)
	{
		cyl->diameter -= 1;
		cyl->radius = cyl->diameter * 0.5;
		cyl->square_radius = pow(cyl->radius, 2);
	}
}

/**========================================================================
 *                           chang_mesh_size
========================================================================**/
void	chang_mesh_size(t_data *data, int keycode)
{
	t_event	*mesh;

	mesh = &data->event;
	if (mesh->actual_mesh.ref == NULL)
		return ;
	if (keycode == PLUS)
		handle_plus_key(data);
	else if (keycode == MINUS)
		handle_minus_key(data);
}
