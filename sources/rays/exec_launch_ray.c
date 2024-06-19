#include "exec_launch_ray.h"

/**========================================================================
 *                           EXEC_LAUNCH_RAYS
 *========================================================================**/
void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y)
{
	t_ray	ray;
	t_obj	obj;

	new_ray(&data->cam, &ray, x, y);
	obj.t = BIG_VALUE;
	obj.ref = NULL;
	obj.type = 4;
	get_closest_intersection_sp(data, &ray, &obj);
	get_closest_intersection_cy(data, &ray, &obj);
	get_closest_intersection_pl(data, &ray, &obj);
	put_pxl(mlx, x, y, get_pixel_color(data, &ray, &obj));
}

/**========================================================================
 *                           GET_PIXEL_COLOR
 *========================================================================**/
int	get_pixel_color(t_data *data, t_ray *ray, t_obj *obj)
{
	int		rgb;
	double	inter_bulb;
	t_color	color;

	rgb = 0;
	inter_bulb = is_intersect_sphere(ray, &data->spotlight.bulb, NULL);
	if (obj->t && obj->type == O_SP && obj->ref && !inter_bulb)
	{
		get_sphere_color(&(t_get_color_params)
		{data, ray, obj->t, obj, &color, NULL});
		rgb = get_color(color.rgb[0], color.rgb[1], color.rgb[2]);
	}
	if (obj->t && obj->type == O_CY && !is_behind_cam(obj->t) && obj->ref
		&& !inter_bulb)
	{
		get_cylinder_color(data, ray, obj, &color);
		rgb = get_color(color.rgb[0], color.rgb[1], color.rgb[2]);
	}
	get_pixel_color_2(&(t_get_pixel_color_2_params){data, ray, obj, &rgb,
		&inter_bulb, &color});
	return (rgb);
}

/**========================================================================
 *                           GET_PIXEL_COLOR_2
 *========================================================================**/
void	get_pixel_color_2(t_get_pixel_color_2_params *params)
{
	t_obj	*obj;
	t_data	*data;
	t_color	*color;
	int		*rgb;
	double	*inter_bulb;

	obj = params->obj;
	data = params->data;
	color = params->color;
	rgb = params->rgb;
	inter_bulb = params->inter_bulb;
	if (obj->t && obj->type == O_PL && !is_behind_cam(obj->t) && obj->ref
		&& !*inter_bulb)
	{
		get_plane_color(&(t_get_color_params)
		{data, params->ray, obj->t, obj, color, NULL});
		*rgb = get_color(color->rgb[0], color->rgb[1], color->rgb[2]);
	}
	if (obj->ref == NULL && !*inter_bulb)
		*rgb = get_background_color(params->ray, data);
	if (*inter_bulb && !is_behind_cam(*inter_bulb))
		*rgb = get_color(data->spotlight.bulb.color.rgb[0], data->spotlight
				.bulb.color.rgb[1], data->spotlight.bulb.color.rgb[2]);
}

/**========================================================================
 *                           	PUT_PXL
 *========================================================================**/

static void	put_pxl(t_mlx *mlx, int x, int y, unsigned int color)
{
	const double	inverse_eight = 0.125;
	int				pxl_pos;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl_pos = x * mlx->img.bpp * inverse_eight + y * mlx->img.line_len;
		*(unsigned int *)(mlx->img.img_data + pxl_pos) = color;
	}
}
