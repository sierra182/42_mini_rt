/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_disruption_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:45:37 by svidot            #+#    #+#             */
/*   Updated: 2024/06/28 15:12:52 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_disruption_bonus.h"

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
	calculate_uv(sphere, *normal, &u, &v);
	if (sphere->checkerboard == 1)
	{
		checker_color(u, v, size, params->color);
		return ;
	}
	if (sphere->checkerboard == 0 && sphere->bump_map_nbr == -1)
		return ;
	apply_bump_mapping(normal, u, v,
		params);
	(void)light_ray;
}

/**========================================================================
 *                           UV_TO_TEXTURE_COORDINATES
 *========================================================================**/
void	uv_to_texture_coordinates(t_uv_to_texture_params *p)
{
	int	xpm_size_x;
	int	xpm_size_y;

	xpm_size_x = p->sphere->xpm_size_x;
	xpm_size_y = p->sphere->xpm_size_y;
	*(p->x) = (int)(p->u * xpm_size_x);
	*(p->y) = (int)(p->v * xpm_size_y);
	if (*(p->x) < 0)
		*(p->x) = (xpm_size_x + *(p->x) % xpm_size_x) % xpm_size_x;
	if (*(p->y) < 0)
		*(p->y) = (xpm_size_y + *(p->y) % xpm_size_y) % xpm_size_y;
	if (*(p->x) > xpm_size_x - 1)
		*(p->x) = *(p->x) % xpm_size_x ;
	if (*(p->y) > xpm_size_y - 1)
		*(p->y) = *(p->y) % xpm_size_y;
}

/**========================================================================
 *                           GRAY_TO_HEX_STRING
 *========================================================================**/
int	gray_to_hex_string(const char *gray_string, char *hex_output)
{
	int	gray_value;
	int	intensity;

	if (ft_strncmp(gray_string, "black", 5) == 0)
		return (strcpy(hex_output, "#FFFFFF"), 1);
	if (ft_strncmp(gray_string, "white", 5) == 0)
		return (strcpy(hex_output, "#000000"), 1);
	if (ft_strncmp(gray_string, "DimGray", 7) == 0)
		return (strcpy(hex_output, "#696969"), 1);
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
 *                           CHECKER_COLOR
 *========================================================================**/
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
