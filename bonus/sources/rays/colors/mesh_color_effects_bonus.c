#include "mesh_color_effects_bonus.h"

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

int	calculate_spotlight_effect(t_calc_spotlight_effect_params *params)
{
	double	light_attenuat;
	double	light_coef;
	double	spec_light_coef;
	double 	spec_coef;

	light_coef = scalar_product(params->light_ray->ray_norm.dir_vect.axis,
			params->normal->axis);
	normalize_zero_one(&light_coef, 1);
	light_attenuat = calculate_light_attenuation(params->light_ray,
			light_coef * params->params->data->spotlight.intensity);
	spec_light_coef = calculate_light_reflexion(params->params->ray,
		params->light_ray, params->normal);
	add_shading(params->params->ray, params->normal, params->spotlighty_color,
		params->spotlighty_color);
	spec_coef = params->params->data->spotlight.intensity + spec_light_coef;
	color_with_light(params->mesh_color,
		&params->params->data->spotlight.color,
	 	spec_coef * light_attenuat,	params->spotlighty_color);
	return (0);
}

/**========================================================================
 *                           CALCULATE_SPOTLIGHT_EFFECT
 * 
 * ! modifye return type on bonus and mand to void
 *========================================================================**/
int	calculate_spotlight_effect2(t_calc_spotlight_effect_params *params)
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
		params->params->data->spotlight.intensity * light_attenuat,
		params->spotlighty_color);
	add_shading(params->params->ray, params->normal, params->spotlighty_color,
		params->spotlighty_color);
	return (0);
}
