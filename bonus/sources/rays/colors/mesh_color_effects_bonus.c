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

/**========================================================================
 *                           CLAMP_0
 *========================================================================**/
double	clamp_0(double num)
{
	if (num < 0)
		return (0.0);
	return (num);
}

/**========================================================================
 *                           CLAMP_0
 *========================================================================**/
double	clamp_1(double num)
{
	if (num > 1)
		return (1.0);
	return (num);
}
#include <math.h>
double	calculate_light_reflexion(t_ray *ray, t_ray_pack *light_ray, t_ray_vector *normal)
{
	t_ray	light_reflx;
	
	double 			scalar_nl;
	t_ray_vector 	scaled_norm;
	double 			scalar_rl;

	scalar_nl = 2 *scalar_product(normal->axis, light_ray->ray.dir_vect.axis);
	scale_vector(normal->axis, scalar_nl, scaled_norm.axis);
	subtract_vector(light_ray->ray.dir_vect.axis, scaled_norm.axis, light_reflx.dir_vect.axis);
	self_normalize_vector(light_reflx.dir_vect.axis);
	//symmetrize_vector(light_reflx.dir_vect.axis);
	scalar_rl = scalar_product(light_reflx.dir_vect.axis, ray->dir_vect.axis);
	double i_spec;
	i_spec =  pow(clamp_0(scalar_rl), 200) * 1;
	// printf("ispec: %f\n", i_spec);
	return (i_spec);
}

int	calculate_spotlight_effect2(t_ray *ray, t_calc_spotlight_effect_params *params)
{
	double	light_attenuat;
	double	light_coef;
	double	spec_light_coef;
	light_coef = scalar_product(params->light_ray->ray_norm.dir_vect.axis,
			params->normal->axis);
	normalize_zero_one(&light_coef, 1);
	light_attenuat = calculate_light_attenuation(params->light_ray,
			light_coef * params->params->data->spotlight.intensity);
	spec_light_coef = calculate_light_reflexion(ray, params->light_ray, params->normal);

	add_shading(params->params->ray, params->normal, params->spotlighty_color,
		params->spotlighty_color);
	double col =	clamp_1(params->params->data->spotlight.intensity + spec_light_coef);
	color_with_light(params->mesh_color,
		&params->params->data->spotlight.color,
	 	col * light_attenuat,
		params->spotlighty_color);
	return (0);
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
