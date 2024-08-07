/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane_color_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:47:09 by svidot            #+#    #+#             */
/*   Updated: 2024/06/28 07:31:46 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_plane_color_bonus.h"

/**========================================================================
 *                           COMPUTE_PL_NORMAL
 *========================================================================**/
static void	compute_pl_normal(t_get_color_params *params,
	t_ray_vector *normal, t_ray_pack *light_ray)
{
	t_plane	*plane;
	double	scalar_nr;

	plane = (t_plane *) params->mesh->ref;
	get_intersect_point(params->ray, params->mesh->t,
		&light_ray->ray.origin_vect);
	cast_vector_mat_ray(&plane->norm_vect, normal);
	self_normalize_vector(normal->axis);
	scalar_nr = scalar_product(normal->axis, params->ray->dir_vect.axis);
	if (scalar_nr > 0)
		symmetrize_vector(normal->axis);
}

/**========================================================================
 *                         ADD_PL_SPOTLIGHTS_EFFECT
 *========================================================================**/
static void	add_pl_spotlights_effect(t_get_color_params *params,
	t_ray_vector *normal, t_color *spotlighties_color, t_ray_pack *light_ray)
{
	t_color	spotlighty_color;
	t_plane	*plane;
	int		i;

	plane = (t_plane *) params->mesh->ref;
	*spotlighties_color = (t_color){.rgb[0] = 0, .rgb[1] = 0, .rgb[2] = 0};
	i = -1;
	while (++i < params->data->sl_nbr)
	{
		compute_light_ray(&params->data->spotlights[i], light_ray);
		if (has_shadow(params->data, params->mesh, light_ray)
			|| scalar_product(normal->axis, light_ray->ray.dir_vect.axis)
			< 1e-3)
			continue ;
		calculate_spotlight_effect(&(t_calc_spotlight_effect_params)
		{params, &plane->color, normal, &spotlighty_color, light_ray,
			&params->data->spotlights[i]});
		add_color(spotlighties_color, &spotlighty_color, spotlighties_color);
	}
}

/**========================================================================
 *                           GET_PLANE_COLOR
 *========================================================================**/
void	get_plane_color(t_get_color_params *params)
{
	t_color			ambiantly_color;	
	t_color			spotlighties_color;
	t_plane			*plane;

	plane = (t_plane *) params->mesh->ref;
	compute_pl_normal(params, params->normal, params->light_ray);
	calculate_ambiant_effect(params, &plane->color, params->normal,
		&ambiantly_color);
	add_pl_spotlights_effect(params, params->normal, &spotlighties_color,
		params->light_ray);
	add_color(&spotlighties_color, &ambiantly_color, params->color);
}
