#include "exec_launch_ray_bonus.h"

/**========================================================================
 *                         GET_CLOSEST_INTERSECTION
 *========================================================================**/
static void	get_closest_intersection(t_data *data, t_ray *ray, t_obj *obj)
{
	obj->t = BIG_VALUE;
	obj->ref = NULL;
	obj->type = 4;
	get_closest_intersection_sp(data, ray, obj);
	get_closest_intersection_cy(data, ray, obj);
	get_closest_intersection_pl(data, ray, obj);
	get_closest_intersection_tr(data, ray, obj);
}

#include "x_linear_algebra_bonus.h"
/**========================================================================
 *                         CALCULATE_RAY_REFLEXION
 *========================================================================**/
static void	calculate_ray_reflexion(t_ray *ray,
	t_ray_vector *normal, t_ray *reflex_ray)
{
	t_ray_vector	scaled_norm;	
	double			scalar_nr;

	scalar_nr = 2 * scalar_product(normal->axis, ray->dir_vect.axis);
	scale_vector(normal->axis, scalar_nr, scaled_norm.axis);
	subtract_vector(ray->dir_vect.axis, scaled_norm.axis,
		reflex_ray->dir_vect.axis);
	self_normalize_vector(reflex_ray->dir_vect.axis);
}

/**========================================================================
 *                           LAUNCH_REFLEXIONS
 *========================================================================**/
void	launch_reflexions(t_data *data, t_ray *ray, t_obj *obj, t_color *color)
{
	t_ray 			reflex_ray;
	t_color			reflex_color;
	t_ray_vector	normal;
	t_ray_pack		light_ray;
	int 			deep = -1;

	get_closest_intersection(data, ray, obj);
	get_pixel_color(&(t_get_color_params)
		{data, ray, obj, color, &normal, &light_ray});
	while (++deep < 4 && obj->ref)
	{
		reflex_ray.origin_vect = light_ray.ray.origin_vect;
		calculate_ray_reflexion(ray, &normal, &reflex_ray);
		get_closest_intersection(data, &reflex_ray, obj);
		get_pixel_color(&(t_get_color_params)
		{data, &reflex_ray, obj, &reflex_color, &normal, &light_ray});	
		scale_color(&reflex_color, 1, &reflex_color);
		if (!obj->ref)
			scale_color(&reflex_color, 0.1, &reflex_color);
		else
			scale_color(color, 1, color);
		add_color(color, &reflex_color, color);	
		ray = &reflex_ray;	
	}
	apply_aces_tonemap(color);
}

/**========================================================================
 *                           EXEC_LAUNCH_RAYS
 *========================================================================**/
void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y)
{
	t_ray	ray;
	t_obj	obj;
	t_color	color;
	
	new_ray(&data->cam, &ray, x + 0.5f, y + 0.5f);
	launch_reflexions(data, &ray, &obj, &color);
	put_pxl(mlx, x, y, get_color(color.rgb[0], color.rgb[1], color.rgb[2]));
}

/**========================================================================
 *                         EXEC_LAUNCH_RAYS_ANTIA
 *========================================================================**/
void	exec_launch_rays_antia(t_mlx *mlx, t_data *data, int x, int y)
{
	t_antia	antia;

	antia.alia = 4.0;
	antia.inv_alia = 0.25;
	antia.ay = y + 0.5f * antia.inv_alia;
	antia.ax = x + 0.5f * antia.inv_alia;
	antia.k = 0;
	antia.i = -1;
	while (++antia.i < antia.alia)
	{
		antia.ax_cpy = antia.ax;
		antia.j = -1;
		while (++antia.j < antia.alia)
		{
			new_ray(&data->cam, &antia.ray, antia.ax_cpy, antia.ay);
			launch_reflexions(data, &antia.ray, &antia.obj,
				&antia.colors[antia.k++]);	
			antia.ax_cpy += antia.inv_alia;
		}
		antia.ay += antia.inv_alia;
	}
	get_average_colors(antia.colors, 16, &antia.average_color);
	put_pxl(mlx, x, y, get_color(antia.average_color.rgb[0],
			antia.average_color.rgb[1], antia.average_color.rgb[2]));
}

/**========================================================================
 *                           	HAS_BULB
 *========================================================================**/
static double	has_bulb(t_data *data, t_ray *ray, t_color *color)
{
	double	inter_bulb;
	int		i;

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
static void	get_pixel_color(t_get_color_params *params)
{
	double	inter_bulb;

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
