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
			t_get_color_params *params);
double	get_bump_coef(t_sphere *sphere, double **bump_map, double u, double v);
int		hex_to_int(const char *hex_string);
void	uv_to_texture_coordinates(t_uv_to_texture_coordinates_params *p);
unsigned char	int_to_grayscale(unsigned int hex_value);

/**========================================================================
 *                           HEX_TO_INT
 *========================================================================**/
int	hex_to_int(const char *hex_string)
{
	// printf("hex_string: >%s<\n", hex_string);
	if (hex_string[0] != '#')
		return (-1);
	return ((int)strtol(hex_string + 1, NULL, 16));
}

void assign_rgb(t_sphere *sphere, t_color *color, double value)
{
	int rgb_value = (int)value;

	color->rgb[0] = (rgb_value >> 16) & 0xFF;
	color->rgb[1] = (rgb_value >> 8) & 0xFF;
	color->rgb[2] = rgb_value & 0xFF;
	if (sphere->bump_flag == 1)
	{
		color->rgb[0] = 255 - color->rgb[0];
		color->rgb[1] = 255 - color->rgb[1];
		color->rgb[2] = 255 - color->rgb[2];
	}
}
/**========================================================================
 *                           GET_BUMP_COEF
 *========================================================================**/
double	get_bump_coef(t_sphere *sphere, double **bump_map, double u, double v)
{
	int		x;
	int		y;

	uv_to_texture_coordinates(&(t_uv_to_texture_coordinates_params){sphere, u, v, &x, &y});
	assign_rgb(sphere, &sphere->color, bump_map[y][x]);
	return (int_to_grayscale(bump_map[y][x]) / 255.0f);
}

/**========================================================================
 *                           CALCULATE_UV
 *========================================================================**/
void	calculate_uv(t_sphere *sphere, t_ray_vector point, double *u, double *v)
{
	int		xpm_size_x;
	int		xpm_size_y;

	xpm_size_x = 360;
	xpm_size_y = 360;
	*u = 0.5 + atan2(point.axis[2], point.axis[0]) / (2 * M_PI);
	*v = 0.5 - asin(point.axis[1]) / M_PI;
	if (sphere->checkerboard && sphere->rotation_angle_x < 0)
		sphere->rotation_angle_x = xpm_size_x - 1;
	if (sphere->checkerboard && sphere->rotation_angle_y < 0)
		sphere->rotation_angle_y = xpm_size_y - 1;
	if (sphere->checkerboard && sphere->rotation_angle_x > xpm_size_x)
		sphere->rotation_angle_x = 0;
	if (sphere->checkerboard && sphere->rotation_angle_y > xpm_size_y)
		sphere->rotation_angle_y = 0;
	*u += sphere->rotation_angle_x / xpm_size_x;
	*v += sphere->rotation_angle_y / xpm_size_y;
}
