#ifndef IS_INTERSECT_CYLINDER_H
# define IS_INTERSECT_CYLINDER_H

# include "se_mini_struct.h"
# include "x_linear_algebra.h"

double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
double	distance_between_points(t_ray_vector *point1, t_matrix_vector *point2);
double	get_t_from_point(t_ray *ray, t_ray_vector *point);
double	compute_return_value_intersect_disc_plans(double tmp1, double tmp2);
double	compute_return_value_is_intersect_cylinder(double t[],
			t_cylinder *cyl, double proj[]);
double	solve_quadratic_equation(t_ray *ray, t_cylinder *cyl, double *discrim);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
double	intersect_disc_plans(t_ray *ray, t_cylinder *cyl, t_ray_vector	*i);

#endif
