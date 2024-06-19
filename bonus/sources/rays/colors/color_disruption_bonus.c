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

#define TEXTURE_WIDTH 512

void	uv_to_texture_coordinates(double u, double v, int *x, int *y)
{
	*x = (int)(u * TEXTURE_WIDTH);
	*y = (int)(v * TEXTURE_WIDTH);
	if (*x < 0)
		*x = 0;
	if (*y < 0)
		*y = 0;
	if (*x >= TEXTURE_WIDTH)
		*x = TEXTURE_WIDTH - 1;
	if (*y >= TEXTURE_WIDTH)
		*y = TEXTURE_WIDTH - 1;
}

int	gray_to_hex_string(const char *gray_string, char *hex_output)
{
	int	gray_value;
	int	intensity;

	if (ft_strncmp(gray_string, "black", 5) == 0)
		return (strcpy(hex_output, "#FFFFFF"), 1);
	if (ft_strncmp(gray_string, "white", 5) == 0)
		return (strcpy(hex_output, "#000000"), 1);
	if (ft_strncmp(gray_string, "DimGray", 7) == 0)
		return (strcpy(hex_output, "#696969"), 0);
	if (ft_strncmp(gray_string, "gray", 4) != 0)
		return (strcpy(hex_output, "#000000"), 0);
	gray_value = ft_atoi(gray_string + 4);
	if (gray_value < 0)
		gray_value = 0;
	if (gray_value > 100)
		gray_value = 100;
	intensity = (int)(gray_value * 255 / 100);
	sprintf(hex_output, "#%02X%02X%02X", intensity, intensity, intensity);
	return (1);
}

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

/**========================================================================
 *                           MODIF_UV
 *========================================================================**/
void	modif_uv(t_get_color_params *params, t_ray_pack *light_ray,
	int size, t_ray_vector	*normal)
{
	double		u;
	double		v;
	double		**bump_map;
	double		bump_coef;
	t_sphere	*sphere;

	sphere = (t_sphere *) params->mesh->ref;
	if (sphere->checkerboard == 0 && sphere->bump_map_nbr == -1)
		return ;
	calculate_uv(*normal, &u, &v);
	if (sphere->checkerboard == 1)
	{
		checker_color(u, v, size, params->color);
		return ;
	}
	bump_map = params->data->bump_maps[sphere->bump_map_nbr];
	bump_coef = get_bump_coef(bump_map, u, v);
	apply_bump_mapping(normal, u, v, bump_map);
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

void	checker_color(double u, double v, int checker_size, t_color *color)
{
	int	u_index;
	int	v_index;
	int	is_checker;

	u_index = (int)(u * checker_size);
	v_index = (int)(v * checker_size);
	is_checker = (u_index % 2 == v_index % 2);
	if (is_checker)
	{
		color->rgb[0] *= 0.3;
		color->rgb[1] *= 0.3;
		color->rgb[2] *= 0.3;
	}
}