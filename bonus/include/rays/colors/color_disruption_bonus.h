#ifndef COLOR_DISRUPTION_BONUS_H
# define COLOR_DISRUPTION_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"
# include "libft.h"
# include <string.h>
# include <stdlib.h>
# include <math.h>

void	clamp_rgb_0(t_color *color);
void	modif_uv(t_get_color_params *params, t_ray_pack *light_ray, int size,
			t_ray_vector	*normal);
void	calculate_uv(t_sphere *sphere, t_ray_vector point, double *u,
			double *v);
void	checker_color(double u, double v, int checker_size, t_color *color);
void	apply_bump_mapping(t_ray_vector *normal, double u, double v,
			t_get_color_params *params);
double	get_bump_coef(t_sphere *sphere, double **bump_map, double u, double v);
int		hex_to_int(const char *hex_string);

#endif
