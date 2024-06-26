/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere_color_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:47:15 by svidot            #+#    #+#             */
/*   Updated: 2024/06/28 20:39:49 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_sphere_color_bonus.h"

/**========================================================================
 *                           COMPUTE_SPHERE_NORMAL
 *========================================================================**/
static void	compute_sph_normal(t_get_color_params *params, t_ray_vector *normal,
t_ray_pack *light_ray)
{
	t_sphere		*sphere;

	sphere = (t_sphere *) params->mesh->ref;
	get_intersect_point(params->ray, params->mesh->t,
		&light_ray->ray.origin_vect);
	subtract_vector(light_ray->ray.origin_vect.axis,
		sphere->origin_vect.axis, normal->axis);
	self_normalize_vector(normal->axis);
	if (sphere->which_t == 2)
		symmetrize_vector(normal->axis);
}

/**========================================================================
 *                         ADD_SPH_SPOTLIGHTS_EFFECT
 *========================================================================**/
static void	add_sph_spotlights_effect(t_get_color_params *params,
	t_ray_vector *normal, t_color *spotlighties_color, t_ray_pack *light_ray)
{
	t_color		spotlighty_color;
	int			i;

	*spotlighties_color = (t_color){.rgb[0] = 0, .rgb[1] = 0, .rgb[2] = 0};
	i = -1;
	while (++i < params->data->sl_nbr)
	{
		compute_light_ray(&params->data->spotlights[i], light_ray);
		if (is_sphere_surface_between(params->mesh->ref,
				&params->data->spotlights[i])
			|| (has_shadow(params->data, params->mesh, light_ray)
				&& scalar_product(light_ray->ray.dir_vect.axis,
					normal->axis) > 0))
			continue ;
		calculate_spotlight_effect(&(t_calc_spotlight_effect_params)
		{params, params->color, normal, &spotlighty_color, light_ray,
			&params->data->spotlights[i]});
		add_color(spotlighties_color, &spotlighty_color, spotlighties_color);
	}
}

/**========================================================================
 *                           GET_SPHERE_COLOR
 *========================================================================**/
void	get_sphere_color(t_get_color_params *params)
{
	t_color			ambiantly_color;	
	t_color			spotlighties_color;
	t_sphere		*sphere;

	sphere = (t_sphere *) params->mesh->ref;
	compute_sph_normal(params, params->normal, params->light_ray);
	*params->color = sphere->color;
	modif_uv(params, params->light_ray, 10, params->normal);
	calculate_ambiant_effect(params, params->color, params->normal,
		&ambiantly_color);
	add_sph_spotlights_effect(params, params->normal, &spotlighties_color,
		params->light_ray);
	add_color(&spotlighties_color, &ambiantly_color, params->color);
}
