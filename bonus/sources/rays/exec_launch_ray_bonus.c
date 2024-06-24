#include "exec_launch_ray_bonus.h"

/**========================================================================
 *                         GET_CLOSEST_INTERSECTION
 *========================================================================**/
static void	get_closest_intersection(t_data *data, t_ray *ray, t_obj *obj)
{
	obj->t = BIG_VALUE;
	obj->ref = NULL;
	obj->type = 5;
	get_closest_intersection_sp(data, ray, obj);
	get_closest_intersection_cy(data, ray, obj);
	get_closest_intersection_pl(data, ray, obj);
	get_closest_intersection_tr(data, ray, obj);
}

/**========================================================================
 *                         GET_REFLEXION_COEFS
 *========================================================================**/
void	get_reflexion_coefs(t_obj *mesh, double *reflex_coef,
	double *color_coef)
{
	*reflex_coef = 1;
	*color_coef = 1;
	if (mesh->ref)
	{
		if (mesh->type == O_SP)
		{
			*reflex_coef = ((t_sphere *)mesh->ref)->reflexion_coef;
			*color_coef = ((t_sphere *)mesh->ref)->color_coef;
		}
		else if (mesh->type == O_CY)
		{
			*reflex_coef = ((t_cylinder *)mesh->ref)->reflexion_coef;
			*color_coef = ((t_cylinder *)mesh->ref)->color_coef;
		}
		else if (mesh->type == O_PL)
		{
			*reflex_coef = ((t_plane *)mesh->ref)->reflexion_coef;
			*color_coef = ((t_plane *)mesh->ref)->color_coef;
		}
		else if (mesh->type == O_TR)
		{
			*reflex_coef = ((t_triangle *)mesh->ref)->reflexion_coef;
			*color_coef = ((t_triangle *)mesh->ref)->color_coef;
		}
	}
}

/**========================================================================
 *                           LAUNCH_REFLEXIONS
 *========================================================================**/
static void	launch_reflexions(t_data *data, t_ray *ray, t_obj *obj,
	t_color *color)
{
	t_reflexion	rflx;

	get_closest_intersection(data, ray, obj);
	get_reflexion_coefs(obj, &rflx.reflex_coef, &rflx.color_coef);
	get_pixel_color(&(t_get_color_params)
	{data, ray, obj, color, &rflx.normal, &rflx.light_ray});
	rflx.deep = -1;
	while (++rflx.deep < 4 && rflx.reflex_coef)
	{
			// if(obj->ref && obj->type == O_PL)
			// 	printf("reflex: %f, color: %f\n", rflx.reflex_coef, rflx.color_coef);
		rflx.reflex_ray.origin_vect = rflx.light_ray.ray.origin_vect;
		calculate_ray_reflexion(ray, &rflx.normal, &rflx.reflex_ray);
		get_closest_intersection(data, &rflx.reflex_ray, obj);
		get_pixel_color(&(t_get_color_params){data, &rflx.reflex_ray, obj,
			&rflx.reflex_color, &rflx.normal, &rflx.light_ray});
		if (obj->ref)
		{
			scale_color(&rflx.reflex_color, rflx.reflex_coef, &rflx.reflex_color);
			scale_color(color, rflx.color_coef, color);
		}
		else
			scale_color(&rflx.reflex_color, 1, &rflx.reflex_color);			
		add_color(color, &rflx.reflex_color, color);
		get_reflexion_coefs(obj, &rflx.reflex_coef, &rflx.color_coef);
		ray = &rflx.reflex_ray;
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
color.rgb[0] = 0;
	color.rgb[1] = 0;
	color.rgb[2] = 0;
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
	int w = -1;
	while (++w < 16)
	{
		antia.colors[w].rgb[0] = 0;
		antia.colors[w].rgb[1] = 0;
		antia.colors[w].rgb[2] = 0;
	}
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
