#ifndef GET_CYLINDER_COLOR_DISCS_H
# define GET_CYLINDER_COLOR_DISCS_H

# include "se_mini_struct.h"
# include "x_linear_algebra.h"

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
void	add_lightening(t_add_lightening_params *params);
void	add_self_shadowing(double light_coef, double light_attenuation,
			t_color *color);
int		has_shadow(t_data *data, t_ray_vector *normal, void *mesh,
			t_ray_pack *light_ray);
int		are_light_and_cam_in_different_cyl_space(t_ray_vector *normal,
			t_spotlight *light, t_cylinder *cyl, t_cam *cam);
int		calculate_spotlight_effect(t_calc_spotlight_effect_params *params);
void	calculate_ambiant_effect(t_get_color_params *params,
			t_color *mesh_color, t_ray_vector *normal,
			t_color *ambiantly_color);
void	calculate_ray_pack(t_ray_pack *ray_pack);

#endif
