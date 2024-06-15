#ifndef GET_CYLINDER_COLOR_DISCS_BONUS_H
# define GET_CYLINDER_COLOR_DISCS_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

void		get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
void		add_self_shadowing(double light_coef, double light_attenuation,
				t_color *color);
int			has_shadow(t_data *data, void *mesh, t_ray_pack *light_ray);
int			are_light_and_cam_in_different_cyl_space(t_ray_vector *normal,
				t_spotlight *light, t_cylinder *cyl, t_cam *cam);
void		calculate_ambiant_effect(t_get_color_params *params,
				t_color *mesh_color, t_ray_vector *normal,
				t_color *ambiantly_color);
void		apply_aces_tonemap(t_color *color);
void		handle_normal_symmetrization(t_get_color_params *params,
				t_ray_vector *normal, t_ray *light_ray);
static int	is_ambianced_only(t_spotlight *spotlight,
				t_get_color_params *params,	t_ray_pack *light_ray,
				double *light_coef);
void		calculate_spotlight_effect(t_calc_spotlight_effect_params *params);
void		compute_light_ray(t_spotlight *spotlight, t_ray_pack *light_ray);

#endif