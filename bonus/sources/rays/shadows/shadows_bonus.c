/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:48:13 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 15:48:14 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadows_bonus.h"

/**========================================================================
 *                           HAS_SPHERE_SHADOW
 *========================================================================**/
static int	has_sphere_shadow(t_data *data, t_obj *mesh, t_ray_pack *light_ray)
{
	int				i;
	double			t;
	double			mesh_mag;
	t_ray_vector	inter_pt;

	i = -1;
	while (++i < data->sp_nbr)
	{
		if (mesh->ref && (void *) &data->spheres[i] != mesh->ref)
		{
			t = is_intersect_sphere(&light_ray->ray_norm,
					&data->spheres[i], NULL);
			if (t)
			{
				get_local_intersect_point(&light_ray->ray_norm, t, &inter_pt);
				mesh_mag = get_vector_magnitude(inter_pt.axis);
				if (mesh_mag - 1e-6 < light_ray->magnitude)
					return (1);
			}
		}
	}
	return (0);
}

/**========================================================================
 *                           HAS_CYLINDER_SHADOW
 *========================================================================**/
static int	has_cylinder_shadow(t_data *data, t_obj *mesh,
	t_ray_pack *light_ray)
{
	int				i;
	double			t;
	double			mesh_mag;
	t_ray_vector	inter_pt;

	i = -1;
	while (++i < data->cy_nbr)
	{
		if (mesh->ref && (void *) & data->cylinders[i] != mesh->ref)
		{
			t = is_intersect_cylinder(&light_ray->ray_norm,
					&data->cylinders[i], NULL);
			if (t)
			{
				get_local_intersect_point(&light_ray->ray_norm, t, &inter_pt);
				mesh_mag = get_vector_magnitude(inter_pt.axis);
				if (mesh_mag - 1e-6 < light_ray->magnitude)
					return (1);
			}
		}
	}
	return (0);
}

/**========================================================================
 *                           HAS_PLANE_SHADOW
 *========================================================================**/
static int	has_plane_shadow(t_data *data, t_obj *mesh, t_ray_pack *light_ray)
{
	int				i;
	double			t;
	double			mesh_mag;
	t_ray_vector	inter_pt;

	i = -1;
	while (++i < data->pl_nbr)
	{
		if (mesh->ref && (void *) &data->planes[i] != mesh->ref)
		{
			t = is_intersect_plane(&light_ray->ray_norm,
					&data->planes[i], NULL);
			if (t)
			{
				get_local_intersect_point(&light_ray->ray_norm, t, &inter_pt);
				mesh_mag = get_vector_magnitude(inter_pt.axis);
				if (mesh_mag - 1e-6 < light_ray->magnitude)
					return (1);
			}
		}
	}
	return (0);
}

/**========================================================================
 *                           HAS_TRIANGLE_SHADOW
 *========================================================================**/
static int	has_triangle_shadow(t_data *data, t_obj *mesh,
	t_ray_pack *light_ray)
{
	int				i;
	double			t;
	double			mesh_mag;
	t_ray_vector	inter_pt;

	i = -1;
	while (++i < data->tr_nbr)
	{
		if (mesh->ref && (void *) &data->triangles[i] != mesh->ref)
		{
			t = is_intersect_triangle(&light_ray->ray_norm,
					&data->triangles[i], NULL);
			if (t)
			{
				get_local_intersect_point(&light_ray->ray_norm, t, &inter_pt);
				mesh_mag = get_vector_magnitude(inter_pt.axis);
				if (mesh_mag - 1e-6 < light_ray->magnitude)
					return (1);
			}
		}
	}
	return (0);
}

/**========================================================================
 *                           HAS_SHADOW
 *========================================================================**/
int	has_shadow(t_data *data, t_obj *mesh, t_ray_pack *light_ray)
{
	if (has_sphere_shadow(data, mesh, light_ray)
		|| has_cylinder_shadow(data, mesh, light_ray)
		|| has_plane_shadow(data, mesh, light_ray)
		|| has_triangle_shadow(data, mesh, light_ray))
		return (1);
	return (0);
}
