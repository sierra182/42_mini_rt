#include "shadows_exclusion.h"

int	is_sphere_surface_between(t_sphere *sphere, t_spotlight *spotlight)
{
	t_matrix_vector	subt_vect;
	double			sphere_light_mag;

	subtract_vector(spotlight->origin_vect.axis, sphere->origin_vect.axis,
		subt_vect.axis);
	sphere_light_mag = get_vector_magnitude(subt_vect.axis);
	return ((sphere_light_mag > sphere->radius
			&& sphere->which_t == 2)
		|| (sphere_light_mag < sphere->radius
			&& sphere->which_t == 1));
}

int	is_cylinder_surface_between( t_cylinder *cyl, t_ray_vector *normal,
	double mesh[])
{
	t_ray			ray;
	t_ray_vector	subt_vect;
	t_ray_vector	inter_vect;
	double			cyl_light_mag;

	cast_vector_mat_ray(&cyl->axis_vect, &ray.dir_vect);
	cast_vector_mat_ray(&cyl->origin_vect, &ray.origin_vect);
	subtract_vector(mesh, cyl->origin_vect.axis, subt_vect.axis);
	self_normalize_vector(ray.dir_vect.axis);
	scale_vector(ray.dir_vect.axis, scalar_product(ray.dir_vect.axis,
			subt_vect.axis), inter_vect.axis);
	subtract_vector(inter_vect.axis, subt_vect.axis, subt_vect.axis);
	cyl_light_mag = get_vector_magnitude(subt_vect.axis);
	return ((cyl_light_mag >= cyl->radius
			&& cyl->which_t == 2)
		|| (cyl_light_mag <= cyl->radius
			&& cyl->which_t == 1));
}
