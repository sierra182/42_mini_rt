/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder_color_discs_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:46:55 by svidot            #+#    #+#             */
/*   Updated: 2024/06/27 14:34:18 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cylinder_color_discs_bonus.h"

/**========================================================================
 *                           ADD_DISC_SPOTLIGHTS_EFFECT
 *========================================================================**/
static void	add_disc_spotlights_effect(t_get_color_params *params,
	t_ray_vector *normal, t_color *spotlighties_color, t_ray_pack *light_ray)
{
	t_color		spotlighty_color;
	double		light_coef;
	t_cylinder	*cyl;
	int			i;

	cyl = ((t_cylinder *) params->mesh->ref);
	*spotlighties_color = (t_color){.rgb[0] = 0, .rgb[1] = 0, .rgb[2] = 0};
	i = -1;
	while (++i < params->data->sl_nbr)
	{
		compute_light_ray(&params->data->spotlights[i], light_ray);
		handle_normal_symmetrization(params, params->normal, &light_ray->ray);
		light_coef = scalar_product(params->normal->axis,
				light_ray->ray.dir_vect.axis);
		if (is_ambianced_only(&params->data->spotlights[i], params, light_ray,
				&light_coef))
			continue ;
		calculate_spotlight_effect(&(t_calc_spotlight_effect_params)
		{params, &cyl->color, normal, &spotlighty_color, light_ray,
			&params->data->spotlights[i]});
		add_color(spotlighties_color, &spotlighty_color, spotlighties_color);
	}
}

/**========================================================================
 *                           GET_CYLINDER_COLOR_DISCS
 *========================================================================**/
void	get_cylinder_color_discs(t_get_color_params *params)
{
	t_color		ambiantly_color;
	t_color		spotlighties_color;
	double		view_dot_normal;
	t_cylinder	*cyl;

	cyl = ((t_cylinder *) params->mesh->ref);
	cast_vector_mat_ray(&cyl->axis_vect, params->normal);
	self_normalize_vector(params->normal->axis);
	get_intersect_point(params->ray, params->mesh->t,
		&params->light_ray->ray.origin_vect);
	view_dot_normal = scalar_product(params->normal->axis,
			params->ray->dir_vect.axis);
	if (view_dot_normal > 0.0)
		symmetrize_vector(params->normal->axis);
	calculate_ambiant_effect(params, &cyl->color, params->normal,
		&ambiantly_color);
	add_disc_spotlights_effect(params, params->normal, &spotlighties_color,
		params->light_ray);
	add_color(&spotlighties_color, &ambiantly_color, params->color);
}

/**========================================================================
 *                           HANDLE_NORMAL_SYMMETRIZATION
 *========================================================================**/
static void	handle_normal_symmetrization(t_get_color_params *params,
	t_ray_vector *normal, t_ray *light_ray)
{
	double		light_dot_normal;
	t_cylinder	*cyl;

	cyl = ((t_cylinder *) params->mesh->ref);
	light_dot_normal = scalar_product(normal->axis, light_ray->dir_vect.axis);
	if (light_dot_normal < 0 && cyl->which_t == 2)
		symmetrize_vector(normal->axis);
}

/**========================================================================
 *                           IS_AMBIANCED_ONLY
 *========================================================================**/
static int	is_ambianced_only(t_spotlight *spotlight,
	t_get_color_params *params, t_ray_pack *light_ray, double *light_coef)
{
	t_cylinder		*cyl;

	cyl = ((t_cylinder *) params->mesh->ref);
	if (has_shadow(params->data, params->mesh, light_ray)
		|| *light_coef < 0.0 || are_light_and_cam_in_different_cyl_space
		(params->normal, spotlight, cyl, &params->data->cam))
		return (1);
	return (0);
}
