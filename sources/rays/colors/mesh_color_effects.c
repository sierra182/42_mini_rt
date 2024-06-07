#include "se_mini_struct.h"
#include "x_linear_algebra.h"

double	calculate_light_attenuation(t_ray *light_ray, double intensity);

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

void	color_with_light(t_color *mesh_color,
	t_color *light_color, double intensity, t_color *new_color)
{
	t_color	scaled_color;

	scale_color(light_color, intensity,
		&scaled_color);
	get_average_color(&scaled_color, mesh_color, new_color);
	scale_color(new_color, intensity, new_color);
}

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
	t_ray	light_ray_cpy;

	light_ray_cpy = *params->light_ray;
	normalize_vector(light_ray_cpy.dir_vect.axis);
	light_coef = scalar_product(light_ray_cpy.dir_vect.axis,
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

// int	calculate_spotlight_effect(t_calc_spotlight_effect_params *params)
// {
// 	double	light_attenuat;
// 	double 	light_coef;
// 	t_ray	light_ray_cpy;

// 	light_ray_cpy = *params->light_ray;
// 	normalize_vector(light_ray_cpy.dir_vect.axis);
// 	light_coef = scalar_product(light_ray_cpy.dir_vect.axis,
// 		params->normal->axis);
// 	normalize_zero_one(&light_coef, 1);
// 	// light_coef = aces_tonemap(light_coef);
// 	light_attenuat = calculate_light_attenuation(params->light_ray,
// 		light_coef * params->params->data->spotlight.intensity);
// 	//  light_attenuat = aces_tonemap(light_attenuat);
// 	color_with_light(params->mesh_color,
// 		&params->params->data->spotlight.color,
// 			params->params->data->spotlight.intensity * light_attenuat * 1,
// 			params->spotlighty_color);	
// 	add_shading(params->params->ray, params->normal, params->spotlighty_color,
// 		params->spotlighty_color);
// 	// printf("sphere light_attenuat: %f\n", light_attenuat);

// 	//  add_lightening(&(t_add_lightening_params){params->light_ray,
// 	// 	params->normal,	&params->params->data->spotlight,
// 	// 	params->spotlighty_color, params->spotlighty_color,
// 	// 	&light_attenuat, &light_coef});//!lightcoef
// 	return (0);	
// }
// double aces_tonemap(double x);
// void	apply_aces_to_color(t_color *color);

// void	add_lightening(t_add_lightening_params *params) 
// {	
// 	t_color	subt_color;
// 	t_color	scaled_color;
// 	t_ray	light_ray_cpy;

// 	light_ray_cpy = *params->light_ray;
// 	normalize_vector(light_ray_cpy.dir_vect.axis); //!opt
// 	*params->light_coef = scalar_product(light_ray_cpy.dir_vect.axis,
// 			params->normal->axis);
// 	normalize_zero_one(params->light_coef, 1);
	
// 	// *params->light_coef = aces_tonemap(*params->light_coef);
// 	// printf("sphere lightray : %f, %f, %f\n", params->light_ray->dir_vect.axis[0], params->light_ray->dir_vect.axis[1], params->light_ray->dir_vect.axis[2]);
// 	*params->light_attenuat = calculate_light_attenuation(params->light_ray,
// 			*params->light_coef * params->spotlight->intensity);
// 	//  *params->light_attenuat = aces_tonemap(*params->light_attenuat);
// 	// printf("sphere light_attenuat: %f\n", *params->light_attenuat);
// 	subtract_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255},
// 		params->color, &subt_color);
// 	//scale_color(params->color, *params->light_attenuat * 1, params->res_color);
// 	scale_color(&subt_color, *params->light_attenuat * 0.00000125, &scaled_color);
// 	//add_color(&scaled_color, params->color, params->res_color);
// 	// apply_aces_to_color(params->res_color);
	
// }

// void	color_with_light(t_color *mesh_color,
// 	t_color *light_color, double intensity, t_color *new_color)
// {
// 	t_color	scaled_color;

// 	scale_color(light_color, intensity,
// 		&scaled_color);
// 	multiply_colors(mesh_color, &scaled_color, new_color);
// }