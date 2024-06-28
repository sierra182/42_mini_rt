/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_intersection_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:47:39 by svidot            #+#    #+#             */
/*   Updated: 2024/06/28 07:32:08 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_closest_intersection_bonus.h"

/**========================================================================
 *                           FIND_CLOSEST_INTERSECTION
 *========================================================================**/
void	find_closest_intersection(t_intersection_params params)
{
	int		i;
	double	t;

	i = 0;
	while (i < params.obj_nbr)
	{
		t = params.intersect_func(&params.ray,
				((char **)params.objects)[i], params.i);
		if (t && t < params.obj->t - 1e-6)
		{
			params.obj->t = t;
			params.obj->type = params.obj_type;
			params.obj->ref = ((void **)params.objects)[i];
		}
		i++;
	}
}

/**========================================================================
 *                           GET_CLOSEST_INTERSECTION_SP
 *========================================================================**/
void	get_closest_intersection_sp(t_data *data, t_ray *ray, t_obj *obj)
{
	t_intersection_params	params_sp;
	t_sphere				*sphere_addresses[OBJ_MAX_NBR];
	int						i;

	i = -1;
	while (++i < data->sp_nbr)
		sphere_addresses[i] = &(data->spheres[i]);
	params_sp.objects = sphere_addresses;
	params_sp.ray = *ray;
	params_sp.obj_nbr = data->sp_nbr;
	params_sp.intersect_func = is_intersect_sphere;
	params_sp.obj = obj;
	params_sp.obj_type = O_SP;
	params_sp.i = NULL;
	find_closest_intersection(params_sp);
}

/**========================================================================
 *                           GET_CLOSEST_INTERSECTION_CY
 *========================================================================**/
void	get_closest_intersection_cy(t_data *data, t_ray *ray, t_obj *obj)
{
	t_intersection_params	params_cy;
	t_cylinder				*cylinders_addresses[OBJ_MAX_NBR];
	int						i;

	i = -1;
	while (++i < data->cy_nbr)
		cylinders_addresses[i] = &(data->cylinders[i]);
	params_cy.objects = cylinders_addresses;
	params_cy.ray = *ray;
	params_cy.obj_nbr = data->cy_nbr;
	params_cy.intersect_func = is_intersect_cylinder;
	params_cy.obj = obj;
	params_cy.obj_type = O_CY;
	params_cy.i = NULL;
	find_closest_intersection(params_cy);
}

/**========================================================================
 *                           GET_CLOSEST_INTERSECTION_PL
 *========================================================================**/
void	get_closest_intersection_pl(t_data *data, t_ray *ray, t_obj *obj)
{
	t_intersection_params	params_pl;
	t_plane					*planes_addresses[OBJ_MAX_NBR];
	int						i;

	i = -1;
	while (++i < data->pl_nbr)
		planes_addresses[i] = &(data->planes[i]);
	params_pl.objects = planes_addresses;
	params_pl.ray = *ray;
	params_pl.obj_nbr = data->pl_nbr;
	params_pl.intersect_func = is_intersect_plane;
	params_pl.obj = obj;
	params_pl.obj_type = O_PL;
	params_pl.i = NULL;
	find_closest_intersection(params_pl);
}

/**========================================================================
 *                           GET_CLOSEST_INTERSECTION_TR
 *========================================================================**/
void	get_closest_intersection_tr(t_data *data, t_ray *ray, t_obj *obj)
{
	t_intersection_params	params_tr;
	t_triangle				*triangles_addresses[OBJ_MAX_NBR];
	int						i;

	i = -1;
	while (++i < data->tr_nbr)
		triangles_addresses[i] = &(data->triangles[i]);
	params_tr.objects = triangles_addresses;
	params_tr.ray = *ray;
	params_tr.obj_nbr = data->tr_nbr;
	params_tr.intersect_func = is_intersect_triangle;
	params_tr.obj = obj;
	params_tr.obj_type = O_TR;
	params_tr.i = NULL;
	find_closest_intersection(params_tr);
}
