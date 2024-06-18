#ifndef GET_SPHERE_COLOR_BONUS_H
# define GET_SPHERE_COLOR_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

int		has_shadow(t_data *data, t_obj *mesh, t_ray_pack *light_ray);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
int		is_sphere_surface_between(t_sphere *sphere, t_spotlight *spotlight);
void	calculate_ambiant_effect(t_get_color_params *params,
			t_color *mesh_color, t_ray_vector *normal,
			t_color *ambiantly_color);
void	apply_aces_tonemap(t_color *color);
void	calculate_spotlight_effect(t_calc_spotlight_effect_params *params);
void	compute_light_ray(t_spotlight *spotlight, t_ray_pack *light_ray);

#endif