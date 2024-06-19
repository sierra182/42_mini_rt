#include "se_mini_struct_bonus.h"
#include "x_linear_algebra_bonus.h"
#include "libft.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

void	clamp_rgb_0(t_color *color);
void	modif_uv(t_get_color_params *params, t_ray_pack *light_ray, int size,
			t_ray_vector	*normal);
void	calculate_uv(t_ray_vector point, double *u, double *v);
void	checker_color(double u, double v, int checker_size, t_color *color);
void	apply_bump_mapping(t_ray_vector *normal, double u, double v,
			double **bump_map);
void	calculate_uv(t_ray_vector point, double *u, double *v);
double	get_bump_coef(double **bump_map, double u, double v);
int		hex_to_int(const char *hex_string);
void	uv_to_texture_coordinates(double u, double v, int *x, int *y);

int	hex_to_int(const char *hex_string)
{
	int	color_value;

	if (hex_string[0] != '#')
		return (-1);
	color_value = (int)strtol(hex_string + 1, NULL, 16);
	return (color_value);
}

double	get_bump_coef(double **bump_map, double u, double v)
{
	int		x;
	int		y;
	double	bump_coef;

	uv_to_texture_coordinates(u, v, &x, &y);
	bump_coef = bump_map[x][y];
	return (bump_coef);
}

void	calculate_uv(t_ray_vector point, double *u, double *v)
{
	double	theta;
	double	phi;

	theta = atan2(point.axis[2], point.axis[0]);
	phi = asin(point.axis[1]);
	*u = 0.5 + theta / (2 * M_PI);
	*v = 0.5 - phi / M_PI;
}
