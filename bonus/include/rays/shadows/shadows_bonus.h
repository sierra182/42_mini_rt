#ifndef SHADOWS_BONUS_H
# define SHADOWS_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

void	get_local_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
double	is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder,
			t_ray_vector *i);
double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
int		is_in_cylinder(t_ray_vector *normal, t_cylinder *cyl, double mesh[]);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);

#endif
