#include "ray_utils_bonus.h"

/**========================================================================
 *                           IS_BEHIND_CAM
 *========================================================================**/
int	is_behind_cam(double t)
{
	return (t <= 0.0);
}

/**========================================================================
 *                           GET_INTERSECT_POINT
 *========================================================================**/
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector	scaled_vect;

	scale_vector(ray->dir_vect.axis, t, scaled_vect.axis);
	add_vector(ray->origin_vect.axis, scaled_vect.axis, inter_pt->axis);
}

/**========================================================================
 *                           GET_LOCAL_INTERSECT_POINT
 *========================================================================**/
void	get_local_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	scale_vector(ray->dir_vect.axis, t, inter_pt->axis);
}

/**========================================================================
 *                           COMPUTE_LIGHT_RAY
 *========================================================================**/
void	compute_light_ray(t_spotlight *spotlight, t_ray_pack *light_ray)
{
	subtract_vector(spotlight->origin_vect.axis,
		light_ray->ray.origin_vect.axis, light_ray->ray.dir_vect.axis);
	light_ray->ray_norm.origin_vect = light_ray->ray.origin_vect;
	light_ray->magnitude = get_vector_magnitude(light_ray->ray.dir_vect.axis);
	normalize_vector(light_ray->ray.dir_vect.axis, light_ray->magnitude,
		light_ray->ray_norm.dir_vect.axis);
}

/**========================================================================
 *                           GET_BACKGROUND_COLOR
 *========================================================================**/
int	get_background_color(t_ray *ray, t_data *data)
{
	int		color[2];
	int		rgb[3];
	double	dir;
	t_color	*bg_color;
	double	intensity;

	intensity = data->ambiant_light.intensity;
	bg_color = (t_color *)&data->ambiant_light.color;
	dir = (ray->dir_vect.axis[1] + 1.0) * 0.5;
	color[0] = get_color(intensity * 255, intensity * 255, intensity * 255);
	color[1] = get_color(bg_color->rgb[0] * intensity, bg_color->rgb[1]
			* intensity, bg_color->rgb[2] * intensity);
	rgb[0] = (int)((1.0 - dir) * ((color[1] >> 16) & 0xFF) + dir
			* ((color[0] >> 16) & 0xFF));
	rgb[1] = (int)((1.0 - dir) * ((color[1] >> 8) & 0xFF) + dir
			* ((color[0] >> 8) & 0xFF));
	rgb[2] = (int)((1.0 - dir) * (color[1] & 0xFF) + dir * (color[0] & 0xFF));
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
