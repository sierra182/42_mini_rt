#ifndef GET_PLANE_COLOR_BONUS_H
# define GET_PLANE_COLOR_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

int		has_shadow(t_data *data, t_obj *mesh, t_ray_pack *light_ray);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
void	calculate_ambiant_effect(t_get_color_params *params,
			t_color *mesh_color, t_ray_vector *normal,
			t_color *ambiantly_color);
void	apply_aces_tonemap(t_color *color);
void	compute_light_ray(t_spotlight *spotlight, t_get_color_params *params,
	        t_ray_pack *light_ray);

#endif