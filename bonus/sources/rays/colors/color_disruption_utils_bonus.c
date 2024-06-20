#include "se_mini_struct_bonus.h"
#include "x_linear_algebra_bonus.h"
#include "libft.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

void	clamp_rgb_0(t_color *color);
void	modif_uv(t_get_color_params *params, t_ray_pack *light_ray, int size,
			t_ray_vector	*normal);
void	calculate_uv(t_sphere *sphere, t_ray_vector point, double *u,
			double *v);
void	checker_color(double u, double v, int checker_size, t_color *color);
void	apply_bump_mapping(t_ray_vector *normal, double u, double v,
			double **bump_map);
double	get_bump_coef(double **bump_map, double u, double v);
int		hex_to_int(const char *hex_string);
void	uv_to_texture_coordinates(double u, double v, int *x, int *y);

/**========================================================================
 *                           HEX_TO_INT
 *========================================================================**/
int	hex_to_int(const char *hex_string)
{
	if (hex_string[0] != '#')
		return (-1);
	return ((int)strtol(hex_string + 1, NULL, 16));
}

/**========================================================================
 *                           GET_BUMP_COEF
 *========================================================================**/
double	get_bump_coef(double **bump_map, double u, double v)
{
	int		x;
	int		y;

	uv_to_texture_coordinates(u, v, &x, &y);
	if (bump_map && bump_map[x] && bump_map[x][y])
		return (bump_map[x][y]);
}

/**========================================================================
 *                           CALCULATE_UV
 *========================================================================**/
void	calculate_uv(t_sphere *sphere, t_ray_vector point, double *u, double *v)
{
	*u = 0.5 + atan2(point.axis[2], point.axis[0]) / (2 * M_PI);
	*v = 0.5 - asin(point.axis[1]) / M_PI;
	if (sphere->checkerboard && sphere->rotation_angle_x < 0)
		sphere->rotation_angle_x = XPM_SIZE - 1;
	if (sphere->checkerboard && sphere->rotation_angle_y < 0)
		sphere->rotation_angle_y = XPM_SIZE - 1;
	if (sphere->checkerboard && sphere->rotation_angle_x > XPM_SIZE)
		sphere->rotation_angle_x = 0;
	if (sphere->checkerboard && sphere->rotation_angle_y > XPM_SIZE)
		sphere->rotation_angle_y = 0;
	*u += sphere->rotation_angle_x / XPM_SIZE;
	*v += sphere->rotation_angle_y / XPM_SIZE;
}
