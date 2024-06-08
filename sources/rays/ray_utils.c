#include "se_mini_struct.h"
#include "x_linear_algebra.h"

int	is_behind_cam(double t)
{
	return (t <= 0.0);
}

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector	scaled_vect;

	scale_vector(ray->dir_vect.axis, t, scaled_vect.axis);
	add_vector(ray->origin_vect.axis, scaled_vect.axis, inter_pt->axis);
}

void	get_local_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector	scaled_vect;

	scale_vector(ray->dir_vect.axis, t, inter_pt->axis);
}

void	calculate_ray_pack(t_ray_pack *ray_pack)
{
	ray_pack->ray_norm.origin_vect = ray_pack->ray.origin_vect;
	ray_pack->magnitude = get_vector_magnitude(ray_pack->ray.dir_vect.axis);
	normalize_vector(ray_pack->ray.dir_vect.axis, ray_pack->magnitude,
		ray_pack->ray_norm.dir_vect.axis);
}
