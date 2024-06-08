#ifndef GET_CYLINDER_COLOR_H
# define GET_CYLINDER_COLOR_H

# include "se_mini_struct.h"
# include "x_linear_algebra.h"

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
int		has_shadow(t_data *data, t_ray_vector *normal, t_obj *mesh,
			t_ray_pack *light_ray);
void	add_lightening(t_add_lightening_params *params);
int		get_cylinder_color_discs(t_get_color_params *params);
int		is_cylinder_surface_between( t_cylinder *cyl, t_ray_vector *normal,
			double mesh[]);
void	calculate_ray_pack(t_ray_pack *ray_pack);
int		is_in_cyl_height(t_ray_vector *normal, t_cylinder *cyl, double mesh[]);
int		calculate_spotlight_effect(t_calc_spotlight_effect_params *params);
void	calculate_ambiant_effect(t_get_color_params *params,
			t_color *mesh_color, t_ray_vector *normal,
			t_color *ambiantly_color);

#endif
