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
static void	calculate_ray_reflexion(t_ray *ray,
	t_ray_vector *normal, t_ray *reflex_ray)
{
	t_ray_vector	scaled_norm;	
	double			scalar_nr;

	scalar_nr = 2 * scalar_product(normal->axis, ray->dir_vect.axis);
	scale_vector(normal->axis, scalar_nr, scaled_norm.axis);
	subtract_vector(scaled_norm.axis, ray->dir_vect.axis, reflex_ray->dir_vect.axis);
	self_normalize_vector(reflex_ray->dir_vect.axis);
	 symmetrize_vector(reflex_ray->dir_vect.axis);//opti
}
void		get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
void	apply_aces_tonemap(t_color *color);
void	compute_pl_normal(t_get_color_params *params,
	t_ray_vector *normal, t_ray_pack *light_ray);
	void	compute_tr_normal(t_get_color_params *params,
	t_ray_vector *normal, t_ray_pack *light_ray);
void	compute_sph_normal(t_get_color_params *params, t_ray_vector *normal,
t_ray_pack *light_ray);
int	launch_recursive_reflexion(t_data *data, t_ray *ray, t_obj *obj, t_color *color)
{
	t_ray 			reflex_ray;
	t_color			reflex_color;
	t_ray_vector	normal;
	t_ray_pack		light_ray;
	static int		deep;
	// printf("je dois me monter trois fois\n");
	get_closest_intersection(data, ray, obj);
	get_pixel_color(data, ray, obj, color, &normal, &light_ray);
	if (deep++ >= 3)
		return (deep = 0, 1);
	if (obj->ref)
	{
		reflex_ray.origin_vect = light_ray.ray.origin_vect;
		// get_intersect_point(ray, obj->t, &reflex_ray.origin_vect);//!
		calculate_ray_reflexion(ray, &normal, &reflex_ray);
		if(launch_recursive_reflexion(data, &reflex_ray, obj, color))
		{
			add_color(color, &reflex_color, color);
				// apply_aces_tonemap(color);
		}

		// get_closest_intersection(data, &reflex_ray, obj);
		// get_pixel_color(data, &reflex_ray, obj, &reflex_color, &normal, &light_ray);
	}
	return (0);
	// apply_aces_tonemap(color);
}

/**========================================================================
 *                           EXEC_LAUNCH_RAYS
 *========================================================================**/
void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y)
{
	t_ray	ray;
	t_obj	obj;
	t_color	color;
	// color.rgb[0] = 0;
	// color.rgb[1] = 0;
	// color.rgb[2] = 0;
	
	new_ray(&data->cam, &ray, x + 0.5f, y + 0.5f);
	launch_recursive_reflexion(data, &ray, &obj, &color);
	 apply_aces_tonemap(&color);
	// get_closest_intersection(data, &ray, &obj);
	// get_pixel_color(data, &ray, &obj, &color);
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
			launch_recursive_reflexion(data, &antia.ray, &antia.obj, &antia.colors[antia.k]);
			apply_aces_tonemap(&antia.colors[antia.k++]);
			// get_closest_intersection(data, &antia.ray, &antia.obj);
			// get_pixel_color(data, &antia.ray, &antia.obj,
			// &antia.colors[antia.k++]);
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
static void	get_pixel_color(t_data *data, t_ray *ray, t_obj *obj,
	t_color *color, t_ray_vector *normal, t_ray_pack *light_ray)
{
	double	inter_bulb;

	inter_bulb = has_bulb(data, ray, color);
	if (obj->t && obj->type == O_SP && obj->ref && !inter_bulb)
		get_sphere_color(&(t_get_color_params)
		{data, ray, obj->t, obj, color, normal, light_ray});
	if (obj->t && obj->type == O_CY && !is_behind_cam(obj->t) && obj->ref
		&& !inter_bulb)
		get_cylinder_color(data, ray, obj, color, normal, light_ray);
	if (obj->t && obj->type == O_PL && !is_behind_cam(obj->t) && obj->ref
		&& !inter_bulb)
		get_plane_color(&(t_get_color_params)
		{data, ray, obj->t, obj, color, normal, light_ray});
	if (obj->t && obj->type == O_TR && !is_behind_cam(obj->t) && obj->ref
		&& !inter_bulb)
		get_triangle_color(&(t_get_color_params)
		{data, ray, obj->t, obj, color, normal, light_ray});
	if (obj->ref == NULL && !inter_bulb)
		get_background_color(ray, data, color);
}
