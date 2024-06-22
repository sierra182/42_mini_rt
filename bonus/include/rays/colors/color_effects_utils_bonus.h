#ifndef COLOR_UTILS_EFFECTS_BONUS_H
# define COLOR_UTILS_EFFECTS_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

void	get_sphere_color(t_get_color_params *params);
void	get_plane_color(t_get_color_params *params);
void	get_triangle_color(t_get_color_params *params);
void	get_cylinder_color(t_get_color_params *params);
double	is_intersect_sphere(t_ray *ray, void *input_sphere,
			t_ray_vector *i);
int		is_behind_cam(double t);

#endif
