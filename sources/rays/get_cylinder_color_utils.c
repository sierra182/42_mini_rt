#include "x_mini_struct.h"
#include "x_linear_algebra.h"
#include <math.h>

int	is_in_cyl_diam( t_cylinder *cyl, t_ray_vector *normal, double mesh[]);

/**========================================================================
 *                           is_in_cyl_height
 *========================================================================**/
int	is_in_cyl_height(t_ray_vector *normal, t_cylinder *cyl, double mesh[])
{
	t_ray_vector	subt_vect;

	subtract_vector(mesh, cyl->origin_vect.axis, subt_vect.axis);
	if (fabs(scalar_product(normal->axis, subt_vect.axis)) < cyl->height * 0.5)
		return (1);
	return (0);
}

/**========================================================================
 *                           is_in_cylinder
 *========================================================================**/
int	is_in_cylinder(t_ray_vector *normal, t_cylinder *cyl, double mesh[])
{
	return (is_in_cyl_height(normal, cyl, mesh)
		&& is_in_cyl_diam(cyl, normal, mesh));
}

/**========================================================================
 *                 are_light_and_cam_in_different_cyl_space
 *========================================================================**/
int	are_light_and_cam_in_different_cyl_space(t_ray_vector *normal,
	t_spotlight *light, t_cylinder *cyl, t_cam *cam)
{
	if (is_in_cylinder(normal, cyl, light->origin_vect.axis)
		&& is_in_cylinder(normal, cyl, cam->origin_vect.axis))
		return (0);
	if (!is_in_cylinder(normal, cyl, light->origin_vect.axis)
		&& !is_in_cylinder(normal, cyl, cam->origin_vect.axis))
		return (0);
	return (1);
}

/**========================================================================
 *                     cylinder_surface_intersection
 *========================================================================**/
int	cylinder_surface_intersection( t_cylinder *cyl,
	t_ray_vector *normal, double mesh[])
{
	t_ray_vector	subt_vect;
	t_ray_vector	inter_vect;
	t_ray			ray;

	cast_vector_mat_ray(&cyl->axis_vect, &ray.dir_vect);
	cast_vector_mat_ray(&cyl->origin_vect, &ray.origin_vect);
	subtract_vector(mesh, cyl->origin_vect.axis, subt_vect.axis);
	normalize_vector(ray.dir_vect.axis);
	scale_vector(ray.dir_vect.axis, scalar_product(ray.dir_vect.axis,
			subt_vect.axis), inter_vect.axis);
	subtract_vector(inter_vect.axis, subt_vect.axis, subt_vect.axis);
	return ((get_vector_magnitude(subt_vect.axis) >= cyl->diameter * 0.5
			&& cyl->which_t == 2) || ((get_vector_magnitude(subt_vect.axis)
				<= cyl->diameter * 0.5
				&& cyl->which_t == 1)));
}

/**========================================================================
 *                           is_in_cyl_diam
 *========================================================================**/
int	is_in_cyl_diam( t_cylinder *cyl, t_ray_vector *normal, double mesh[])
{
	t_ray_vector	subt_vect;
	t_ray_vector	inter_vect;
	t_ray			ray;

	cast_vector_mat_ray(&cyl->axis_vect, &ray.dir_vect);
	cast_vector_mat_ray(&cyl->origin_vect, &ray.origin_vect);
	subtract_vector(mesh, cyl->origin_vect.axis, subt_vect.axis);
	normalize_vector(ray.dir_vect.axis);
	scale_vector(ray.dir_vect.axis, scalar_product(ray.dir_vect.axis,
			subt_vect.axis), inter_vect.axis);
	subtract_vector(inter_vect.axis, subt_vect.axis, subt_vect.axis);
	if (get_vector_magnitude(subt_vect.axis) <= cyl->diameter * 0.5)
		return (1);
	else
		return (0);
}
