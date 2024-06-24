#include "color_effects_utils_bonus.h"

/**========================================================================
 *                           GET_BACKGROUND_COLOR
 *========================================================================**/
static void	get_background_color(t_ray *ray, t_data *data,
	t_color *back_color)
{
	int		color[2];
	double	dir;
	t_color	*bg_color;
	double	intensity;

	intensity = data->ambiant_light.intensity;
	bg_color = (t_color *)&data->ambiant_light.color;
	dir = (ray->dir_vect.axis[1] + 1.0) * 0.5;
	color[0] = get_color(intensity * 255, intensity * 255, intensity * 255);
	color[1] = get_color(bg_color->rgb[0] * intensity, bg_color->rgb[1]
			* intensity, bg_color->rgb[2] * intensity);
	back_color->rgb[0] = (int)((1.0 - dir) * ((color[1] >> 16) & 0xFF) + dir
			* ((color[0] >> 16) & 0xFF));
	back_color->rgb[1] = (int)((1.0 - dir) * ((color[1] >> 8) & 0xFF) + dir
			* ((color[0] >> 8) & 0xFF));
	back_color->rgb[2] = (int)((1.0 - dir) * (color[1] & 0xFF) + dir
			* (color[0] & 0xFF));
}

/**========================================================================
 *                           	HAS_BULB
 *========================================================================**/
static double	has_bulb(t_data *data, t_ray *ray, t_color *color)
{
	double	inter_bulb;
	int		i;

	inter_bulb = 0.0;
	i = -1;
	while (++i < data->sl_nbr)
	{
		inter_bulb = is_intersect_sphere(ray, &data->spotlights[i].bulb, NULL);
		if (inter_bulb && !is_behind_cam(inter_bulb))
		{
			*color = data->spotlights[i].bulb.color;
			return (inter_bulb);
		}
	}
	return (0.0);
}

/**========================================================================
 *                           GET_PIXEL_COLOR
 *========================================================================**/
void	get_pixel_color(t_get_color_params *params)
{
	double	inter_bulb;
	 	
	// params->color->rgb[0] = 0;
	// params->color->rgb[1] = 0;
	// params->color->rgb[2] = 0;
	inter_bulb = has_bulb(params->data, params->ray, params->color);
	if (params->mesh->t && params->mesh->type == O_SP
		&& params->mesh->ref && !inter_bulb)
		get_sphere_color(params);
	if (params->mesh->t && params->mesh->type == O_CY
		&& !is_behind_cam(params->mesh->t) && params->mesh->ref && !inter_bulb)
		get_cylinder_color(params);
	if (params->mesh->t && params->mesh->type == O_PL
		&& !is_behind_cam(params->mesh->t) && params->mesh->ref && !inter_bulb)
		get_plane_color(params);
	if (params->mesh->t && params->mesh->type == O_TR
		&& !is_behind_cam(params->mesh->t) && params->mesh->ref && !inter_bulb)
		get_triangle_color(params);
	if (params->mesh->ref == NULL && !inter_bulb)
		get_background_color(params->ray, params->data, params->color);
}
