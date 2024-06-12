#include "color_effects_bonus.h"

/**========================================================================
 *                        CALCULATE_LIGHT_REFLEXION
 *========================================================================**/
double	calculate_light_reflexion(t_ray *ray, t_ray_pack *light_ray,
	t_ray_vector *normal)
{
	t_ray_vector 	scaled_norm;
	t_ray			light_reflx;	
	double 			scalar_nl;
	double 			scalar_rl;

	scalar_nl = 2 *scalar_product(normal->axis, light_ray->ray.dir_vect.axis);
	scale_vector(normal->axis, scalar_nl, scaled_norm.axis);
	subtract_vector(light_ray->ray.dir_vect.axis, scaled_norm.axis,
		light_reflx.dir_vect.axis);
	self_normalize_vector(light_reflx.dir_vect.axis);
	scalar_rl = scalar_product(light_reflx.dir_vect.axis, ray->dir_vect.axis);	
	return (pow(clamp_0(scalar_rl), 200) * 1);
}

/**========================================================================
 *                      CALCULATE_LIGHT_ATTENUATION
 *========================================================================**/
double	calculate_light_attenuation(t_ray_pack *light_ray, double intensity)
{
	double			light_mag;
	const double	kc = 0.5;
	const double	kl = 45e-4;
	const double	kq = 75e-25;

	light_mag = light_ray->magnitude;
	return (intensity / (kc + kl * light_mag + kq * light_mag * light_mag));
}

/**========================================================================
 *                           ACES_TONEMAP
 *========================================================================**/
double	aces_tonemap(double x)
{
	const double	a = 2.51;
	const double	b = 0.03;
	const double	c = 2.43;
	const double	d = 0.59;
	const double	e = 0.14;

	return ((x * (a * x + b)) / (x * (c * x + d) + e));
}

/**========================================================================
 *                        APPLY_ACES_TONEMAP
 *========================================================================**/
void	apply_aces_tonemap(t_color *color)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		color->rgb[i] = aces_tonemap(color->rgb[i] / 255.0f) * 255;
	clamp_255(color);
}
