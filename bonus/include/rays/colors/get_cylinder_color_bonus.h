#ifndef GET_CYLINDER_COLOR_BONUS_H
# define GET_CYLINDER_COLOR_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

void		get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
int			has_shadow(t_data *data, t_obj *mesh, t_ray_pack *light_ray);
int			get_cylinder_color_discs(t_get_color_params *params);
int			is_cylinder_surface_between(t_cylinder *cyl, double mesh[]);
int			is_in_cyl_height(t_ray_vector *normal, t_cylinder *cyl,
				double mesh[]);
void		calculate_ambiant_effect(t_get_color_params *params,
				t_color *mesh_color, t_ray_vector *normal,
				t_color *ambiantly_color);
void		apply_aces_tonemap(t_color *color);
static void	get_cylinder_color_cyl(t_get_color_params *params);
static void	handle_projection(t_get_color_params *params, t_ray_vector *normal,
				t_ray *light_ray);
static int	is_ambianced_only(t_spotlight *t_spotlight,
				t_get_color_params *params, t_ray_pack *light_ray);
void		calculate_spotlight_effect(t_calc_spotlight_effect_params *params);
void		compute_light_ray(t_spotlight *spotlight, t_ray_pack *light_ray);

#endif