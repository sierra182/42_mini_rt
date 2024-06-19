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

void	uv_to_texture_coordinates(double u, double v, int *x, int *y)
{
	*x = (int)(u * XPM_size);
	*y = (int)(v * XPM_size);
	if (*x < 0)
		*x = 0;
	if (*y < 0)
		*y = 0;
	if (*x >= XPM_size)
		*x = XPM_size - 1;
	if (*y >= XPM_size)
		*y = XPM_size - 1;
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

/**========================================================================
 *                           MODIF_UV
 *========================================================================**/
void	modif_uv(t_get_color_params *params, t_ray_pack *light_ray,
	int size, t_ray_vector	*normal)
{
	double		u;
	double		v;
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
	apply_bump_mapping(normal, u, v, params->data->bump_maps[sphere->bump_map_nbr]);
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
