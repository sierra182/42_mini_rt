#include "x_mini_struct.h"
#include "x_linear_algebra.h"
#include <math.h>

// int	is_in_cyl_diam( t_cylinder *cyl, t_ray_vector *normal, double mesh[]);

/**========================================================================
 *                           GET_CYLINDER_COLOR_CYL
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

// /**========================================================================
//  *                           PRINT_DELAY
//  *========================================================================**/
// void	print_delay(t_ray_vector *subt_vect, double diam)
// {
// 	static int	delay;

// 	delay = (delay + 1) % 1800;
// 	if (!delay)
// 		printf("mag:%f rayon:%f\n", get_vector_magnitude(subt_vect->axis),
// 			diam * 0.5);
// }

/**========================================================================
 *                           IS_CYLINDER
 *========================================================================**/
int	is_cylinder_surface_between2( t_cylinder *cyl, t_ray_vector *normal,
	double mesh[])
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
				<= cyl->diameter * 0.5 && cyl->which_t == 1)));
}

/**========================================================================
 *                           IS_IN_CYL_HEIGHT
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
 *                           IS_IN_CYLINDER
 *========================================================================**/
int	is_in_cylinder(t_ray_vector *normal, t_cylinder *cyl, double mesh[])
{
	return (is_in_cyl_height(normal, cyl, mesh)
		&& is_in_cyl_diam(cyl, normal, mesh));
}

/**========================================================================
 *                  ARE_LIGHT_AND_CAM_IN_DIFFERENT_CYL_SPACE
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
