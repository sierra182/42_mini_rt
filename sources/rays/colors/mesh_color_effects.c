/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_color_effects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:04:16 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 14:04:17 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_color_effects.h"

/**========================================================================
 *                           ADD_SHADING
 *========================================================================**/
void	add_shading( t_ray *ray, t_ray_vector *normal,
	t_color *color, t_color *res_color)
{
	double	light_coef;
	t_color	scaled_color;

	light_coef = scalar_product(ray->dir_vect.axis, normal->axis);
	normalize_zero_one(&light_coef, 0);
	scale_color(color, light_coef, &scaled_color);
	subtract_color(color, &scaled_color, res_color);
}

/**========================================================================
 *                           COLOR_WITH_LIGHT
 *========================================================================**/
void	color_with_light(t_color *mesh_color,
	t_color *light_color, double intensity, t_color *new_color)
{
	t_color	scaled_color;

	scale_color(light_color, intensity,
		&scaled_color);
	get_average_color(&scaled_color, mesh_color, new_color);
	scale_color(new_color, intensity, new_color);
}

/**========================================================================
 *                           CALCULATE_AMBIANT_EFFECT
 *========================================================================**/
void	calculate_ambiant_effect(t_get_color_params *params,
	t_color *mesh_color, t_ray_vector *normal, t_color *ambiantly_color)
{
	color_with_light(mesh_color, &params->data->ambiant_light.color,
		params->data->ambiant_light.intensity, ambiantly_color);
	add_shading(params->ray, normal, ambiantly_color, ambiantly_color);
}

/**========================================================================
 *                           CALCULATE_SPOTLIGHT_EFFECT
 *========================================================================**/
int	calculate_spotlight_effect(t_calc_spotlight_effect_params *params)
{
	double	light_attenuat;
	double	light_coef;

	light_coef = scalar_product(params->light_ray->ray_norm.dir_vect.axis,
			params->normal->axis);
	normalize_zero_one(&light_coef, 1);
	light_attenuat = calculate_light_attenuation(params->light_ray,
			light_coef * params->params->data->spotlight.intensity);
	color_with_light(params->mesh_color,
		&params->params->data->spotlight.color,
		params->params->data->spotlight.intensity * light_attenuat * 1,
		params->spotlighty_color);
	add_shading(params->params->ray, params->normal, params->spotlighty_color,
		params->spotlighty_color);
	return (0);
}
