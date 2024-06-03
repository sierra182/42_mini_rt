#include "se_mini_struct.h"
#include "x_linear_algebra.h"

double	calculate_light_attenuation(t_ray *light_ray, double intensity)
{
	double			light_mag;
	const double	kc = 1.0;
	const double	kl = 45e-4;
	const double	kq = 75e-25;

	light_mag = get_vector_magnitude(light_ray->dir_vect.axis);
	return (intensity / (kc + kl * light_mag + kq * light_mag * light_mag));
}

void	add_self_shadowing(double light_coef, double light_attenuation,
	t_color *color)
{
	t_color	scaled_color;

	scale_color(color, 1 - light_attenuation * 4, &scaled_color);
	subtract_color(color, &scaled_color, color);
}

void	add_shading2( t_ray *ray, t_ray_vector *normal,
	t_color *color, t_color *res_color)
{
	double	light_coef;
	t_color	scaled_color;

	light_coef = scalar_product(ray->dir_vect.axis, normal->axis);
	
	normalize_zero_one(&light_coef);
	scale_color(color, light_coef, &scaled_color);
	subtract_color(color, &scaled_color, res_color);
}
void	add_shading( t_ray *ray, t_ray_vector *normal,
	t_color *color, t_color *res_color)
{
	double	light_coef;
	t_color	scaled_color;

	light_coef = scalar_product(ray->dir_vect.axis, normal->axis);
	light_coef = (light_coef + 1) * 0.5;
	// normalize_zero_one(&light_coef);
	scale_color(color, light_coef, &scaled_color);
	subtract_color(color, &scaled_color, res_color);
}
void	add_lightening(t_add_lightening_params *params) 
{
	
	t_color	subt_color;
	t_color	scaled_color;

	t_ray	light_ray_cpy;

	light_ray_cpy = *params->light_ray;
	//light_ray_sav = *params->light_ray;
	 normalize_vector(light_ray_cpy.dir_vect.axis); //!opt
	*params->light_coef = scalar_product(light_ray_cpy.dir_vect.axis,
			params->normal->axis);
	normalize_zero_one(params->light_coef);
	subtract_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255},
		params->color, &subt_color);
	*params->light_attenuat = calculate_light_attenuation(params->light_ray,
			*params->light_coef * params->spotlight->intensity);
	scale_color(&subt_color, *params->light_attenuat * 0.825, &scaled_color);
	add_color(&scaled_color, params->color, params->res_color);
}
// void	add_lightening(t_add_lightening_params *params) good
// {
// 	t_ray	light_ray_sav;
// 	t_color	subt_color;
// 	t_color	scaled_color;

// 	light_ray_sav = *params->light_ray;
// 	// normalize_vector(params->light_ray->dir_vect.axis);
// 	*params->light_coef = scalar_product(params->light_ray->dir_vect.axis,
// 			params->normal->axis);
// 	normalize_zero_one(params->light_coef);
// 	subtract_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255},
// 		params->color, &subt_color);
// 	// *params->light_attenuat = calculate_light_attenuation(&light_ray_sav,
// 	// 		*params->light_coef * params->spotlight->intensity);
// 	scale_color(&subt_color, *params->light_attenuat, &scaled_color);
// 	add_color(&scaled_color, params->color, params->res_color);
// }

void	color_with_light(t_color *mesh_color,
	t_color *light_color, double intensity, t_color *new_color)
{
	t_color	scaled_color;

	scale_color(light_color, intensity,
		&scaled_color);
	get_average_color(&scaled_color, mesh_color, new_color);
	scale_color(new_color, intensity, new_color);
}
