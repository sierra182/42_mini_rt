#include "compute_rays_bonus.h"

/**========================================================================
 *                           COMPUTE_LIGHT_RAY
 *========================================================================**/
void	compute_light_ray(t_spotlight *spotlight, t_ray_pack *light_ray)
{
	subtract_vector(spotlight->origin_vect.axis,
		light_ray->ray.origin_vect.axis, light_ray->ray.dir_vect.axis);
	light_ray->ray_norm.origin_vect = light_ray->ray.origin_vect;
	light_ray->magnitude = get_vector_magnitude(light_ray->ray.dir_vect.axis);
	normalize_vector(light_ray->ray.dir_vect.axis, light_ray->magnitude,
		light_ray->ray_norm.dir_vect.axis);
}

/**========================================================================
 *                        CALCULATE_LIGHT_REFLEXION
 *========================================================================**/
double	calculate_light_reflexion(t_ray *ray, t_ray_pack *light_ray,
	t_ray_vector *normal)
{
	t_ray_vector	scaled_norm;
	t_ray			light_reflx;	
	double			scalar_nl;
	double			scalar_rl;

	scalar_nl = 2 * scalar_product(normal->axis, light_ray->ray.dir_vect.axis);
	scale_vector(normal->axis, scalar_nl, scaled_norm.axis);
	subtract_vector(light_ray->ray.dir_vect.axis, scaled_norm.axis,
		light_reflx.dir_vect.axis);
	self_normalize_vector(light_reflx.dir_vect.axis);
	scalar_rl = scalar_product(light_reflx.dir_vect.axis, ray->dir_vect.axis);
	return (pow(clamp_0(scalar_rl), 200) * 1);
}

/**========================================================================
 *                         CALCULATE_RAY_REFLEXION
 *========================================================================**/
void	calculate_ray_reflexion(t_ray *ray,
	t_ray_vector *normal, t_ray *reflex_ray)
{
	t_ray_vector	scaled_norm;	
	double			scalar_nr;

	scalar_nr = 2 * scalar_product(normal->axis, ray->dir_vect.axis);
	scale_vector(normal->axis, scalar_nr, scaled_norm.axis);
	subtract_vector(ray->dir_vect.axis, scaled_norm.axis,
		reflex_ray->dir_vect.axis);
	self_normalize_vector(reflex_ray->dir_vect.axis);
}
