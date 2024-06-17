#ifndef FIND_CLOSEST_INTERSECTION_BONUS_H
# define FIND_CLOSEST_INTERSECTION_BONUS_H

# include "se_mini_struct_bonus.h"
# define OBJ_MAX_NBR 1000

double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
double	is_intersect_cylinder(t_ray *ray, void *input_cyl, t_ray_vector *t);
double	is_intersect_triangle(t_ray *ray, void *input_triangle,
	t_ray_vector *i);
	
#endif
