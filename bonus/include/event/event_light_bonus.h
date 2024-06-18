#ifndef EVENT_LIGHT_BONUS_H
# define EVENT_LIGHT_BONUS_H

# include "se_mini_struct_bonus.h"

void	new_ray(t_cam *cam, t_ray *ray, int x, int y);
double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
int		is_behind_cam(double t);

#endif
