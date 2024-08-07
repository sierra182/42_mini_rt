/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder_color_discs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:03:38 by svidot            #+#    #+#             */
/*   Updated: 2024/06/28 07:40:48 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cylinder_color_discs.h"

/**========================================================================
 *                           GET_CYLINDER_COLOR_DISCS
 *========================================================================**/
void	get_cylinder_color_discs(t_get_color_params *params)
{
	t_ray_pack	light_ray;
	t_color		ambiantly_color;
	t_color		spotlighty_color;
	t_cylinder	*cyl;
	double		light_coef;

	cyl = ((t_cylinder *) params->mesh->ref);
	cast_vector_mat_ray(&cyl->axis_vect, params->normal);
	self_normalize_vector(params->normal->axis);
	get_intersect_point(params->ray, params->t, &light_ray.ray.origin_vect);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray.ray.origin_vect.axis, light_ray.ray.dir_vect.axis);
	calculate_ray_pack(&light_ray);
	handle_normal_symmetrization(params, params->normal, &light_ray.ray);
	calculate_ambiant_effect(params, &cyl->color, params->normal,
		&ambiantly_color);
	light_coef = scalar_product(params->normal->axis,
			light_ray.ray.dir_vect.axis);
	if (is_ambianced_only(params, &light_ray, &light_coef, &ambiantly_color))
		return ;
	calculate_spotlight_effect(&(t_calc_spotlight_effect_params)
	{params, &cyl->color, params->normal, &spotlighty_color, &light_ray});
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	apply_aces_tonemap(params->color);
}

/**========================================================================
 *                           HANDLE_NORMAL_SYMMETRIZATION
 *========================================================================**/
void	handle_normal_symmetrization(t_get_color_params *params, t_ray_vector
*normal, t_ray *light_ray)
{
	double			light_dot_normal;
	double			view_dot_normal;
	t_cylinder		*cyl;

	cyl = ((t_cylinder *) params->mesh->ref);
	view_dot_normal = scalar_product(normal->axis, params->ray->dir_vect.axis);
	if (view_dot_normal > 0.0)
		symmetrize_vector(normal->axis);
	light_dot_normal = scalar_product(normal->axis, light_ray->dir_vect.axis);
	if (light_dot_normal < 0 && cyl->which_t == 2)
		symmetrize_vector(normal->axis);
}

/**========================================================================
 *                           IS_AMBIANCED_ONLY
 *========================================================================**/
static int	is_ambianced_only(t_get_color_params *params,
	t_ray_pack *light_ray, double *light_coef, t_color *ambiantly_color)
{
	t_cylinder		*cyl;

	cyl = ((t_cylinder *) params->mesh->ref);
	if (has_shadow(params->data, params->mesh, light_ray)
		|| *light_coef < 0.0 || are_light_and_cam_in_different_cyl_space
		(params->normal, &params->data->spotlight, cyl, &params->data->cam))
	{
		*params->color = *ambiantly_color;
		apply_aces_tonemap(params->color);
		return (1);
	}
	return (0);
}
