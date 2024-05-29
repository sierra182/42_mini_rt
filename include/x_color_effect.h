#ifndef X_COLOR_EFFECT_H
# define X_COLOR_EFFECT_H

# include "x_mini_struct.h"

double	calculate_light_attenuation(t_ray *light_ray, double intensity);
void	add_self_shadowing(double light_coef, double light_attenuation,
	t_color *color);
void	add_shading( t_ray *ray, t_ray_vector *normal,
	t_color *color, t_color *res_color);
void	add_lightening(t_add_lightening_params *params);
void	color_with_light(t_color *mesh_color,
	t_color *light_color, double intensity, t_color *new_color);

#endif