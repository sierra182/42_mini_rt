#include "exec_launch_ray_bonus.h"


void	get_average_colors(t_color colors[], int n_colors, t_color *average);
/**========================================================================
 *                           EXEC_LAUNCH_RAYS
 *========================================================================**/
// void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y)
// {
// 	t_ray	ray;
// 	t_obj	obj;
// 		printf("%f\n",x);
// 	new_ray(&data->cam, &ray, x, y);
// 	obj.t = BIG_VALUE;
// 	obj.ref = NULL;
// 	obj.type = 5;
// 	get_closest_intersection_sp(data, &ray, &obj);
// 	get_closest_intersection_cy(data, &ray, &obj);
// 	get_closest_intersection_pl(data, &ray, &obj);
// 	get_closest_intersection_tr(data, &ray, &obj);
// 	put_pxl(mlx, x, y, get_pixel_color(data, &ray, &obj));
// }
// void		new_ray(t_cam *cam, t_ray *ray, int x, int y);
void		new_ray(t_cam *cam, t_ray *ray, double x, double y);

/**========================================================================
 *                         EXEC_LAUNCH_RAYS_ANTIA
 *========================================================================**/
void	exec_launch_rays(t_mlx *mlx, t_data *data, double x, double y)//!
{
	double alia = 4.0;
	int		i;
	int		j;
	t_ray	ray;
	t_obj	obj;
	t_color	colors[16];
	t_color	average_color;

	

	double ax, ay;

	ay = y;
	ay += 0.5f / alia;
	int k = 0;
	i = -1;
	while (++i < alia)
	{
		j = -1;
		ax = x;
		ax += 0.5f / alia;
		while (++j < alia)
		{
			new_ray(&data->cam, &ray, ax , ay); //opti div
			obj.t = BIG_VALUE;
			obj.ref = NULL;
			obj.type = 4;
			get_closest_intersection_sp(data, &ray, &obj);
			get_closest_intersection_cy(data, &ray, &obj);
			get_closest_intersection_pl(data, &ray, &obj);
			get_closest_intersection_tr(data, &ray, &obj);
			get_pixel_color(data, &ray, &obj, &colors[k]);//      [((i + 1) * (j + 1)) - 1]);
			
			ax += 1.0f / alia;
				// printf("%d, %d, %d\n", colors[k].rgb[0], colors[k].rgb[1], colors[k].rgb[2]);
			// if( ax > 800.0)
		
			k++;
		}
		ay += 1.0f / alia;	
	}
	get_average_colors(colors, 16, &average_color);
	//   printf("%d, %d, %d\n", average_color.rgb[0], average_color.rgb[1], average_color.rgb[2]);

	put_pxl(mlx, x, y, get_color(average_color.rgb[0], average_color.rgb[1], average_color.rgb[2]));
}

// void	exec_launch_rays(t_mlx *mlx, t_data *data, double x, double y)//!
// {
// 	double alia = 4.0;
// 	int		i;
// 	int		j;
// 	t_ray	ray;
// 	t_obj	obj;
// 	t_color	colors[16];
// 	t_color	average_color;

// 	i = -1;
// 	x += 0.5 / alia;
// 	y += 0.5 / alia;
// 	while (++i < alia)
// 	{
// 		j -1;
// 		while (++j < alia)
// 		{
// 			new_ray(&data->cam, &ray, x + (i + 1.0) / alia, y + (i + 1.0) / alia); //opti div
// 			obj.t = BIG_VALUE;
// 			obj.ref = NULL;
// 			obj.type = 4;
// 			get_closest_intersection_sp(data, &ray, &obj);
// 			get_closest_intersection_cy(data, &ray, &obj);
// 			get_closest_intersection_pl(data, &ray, &obj);
// 			get_closest_intersection_tr(data, &ray, &obj);
// 			get_pixel_color(data, &ray, &obj, &colors[i]);
// 		}
// 		//  new_ray(&data->cam, &ray, x, y);
		
// 		// printf("%d, %d, %d\n", colors[i].rgb[0], colors[i].rgb[1], colors[i].rgb[2]);
// 	}
// 	get_average_colors(colors, alia, &average_color);
// 	// printf("%d, %d, %d\n", average_color.rgb[0], average_color.rgb[1], average_color.rgb[2]);

// 	put_pxl(mlx, x, y, get_color(average_color.rgb[0], average_color.rgb[1], average_color.rgb[2]));
// }
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
		if (inter_bulb)
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
int	get_pixel_color(t_data *data, t_ray *ray, t_obj *obj, t_color *color)
{
	int		rgb;
	double	inter_bulb;
	// t_color	color;

	rgb = 0;
	inter_bulb = has_bulb(data, ray, color);
	if (inter_bulb && !is_behind_cam(inter_bulb))
		rgb = get_color(color->rgb[0], color->rgb[1], color->rgb[2]);
	if (obj->t && obj->type == O_SP && obj->ref && !inter_bulb)
	{
		get_sphere_color(&(t_get_color_params)
		{data, ray, obj->t, obj, color, NULL});
		rgb = get_color(color->rgb[0], color->rgb[1], color->rgb[2]);
	}
	if (obj->t && obj->type == O_CY && !is_behind_cam(obj->t) && obj->ref
		&& !inter_bulb)
	{
		get_cylinder_color(data, ray, obj, color);
		rgb = get_color(color->rgb[0], color->rgb[1], color->rgb[2]);
	}
	get_pixel_color_2(&(t_get_pixel_color_2_params){data, ray, obj, &rgb,
		&inter_bulb, color}, color);
	return (rgb);
}

/**========================================================================
 *                           GET_BACKGROUND_COLOR
 *========================================================================**/
static int	get_background_color2(t_ray *ray, t_data *data, t_color *rcolor)
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
	*rcolor = (t_color){rgb[0], rgb[1], rgb[2]};
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
/**========================================================================
 *                           GET_PIXEL_COLOR_2
 *========================================================================**/
void	get_pixel_color_2(t_get_pixel_color_2_params *params, t_color *color)
{
	t_obj	*obj;
	t_data	*data;
	// t_color	*color;
	int		*rgb;

	obj = params->obj;
	data = params->data;
	color = params->color;
	rgb = params->rgb;
	if (obj->t && obj->type == O_PL && !is_behind_cam(obj->t) && obj->ref
		&& !*params->inter_bulb)
	{
		get_plane_color(&(t_get_color_params)
		{data, params->ray, obj->t, obj, color, NULL});
		*rgb = get_color(color->rgb[0], color->rgb[1], color->rgb[2]);
	}
	if (obj->t && obj->type == O_TR && !is_behind_cam(obj->t) && obj->ref
		&& !*params->inter_bulb)
	{
		get_triangle_color(&(t_get_color_params)
		{data, params->ray, obj->t, obj, color, NULL});
		*rgb = get_color(color->rgb[0], color->rgb[1], color->rgb[2]);
	}
	if (obj->ref == NULL && !*params->inter_bulb)
		*rgb = get_background_color2(params->ray, data, color);
}

// /**========================================================================
//  *                           GET_PIXEL_COLOR
//  *========================================================================**/
// int	get_pixel_color(t_data *data, t_ray *ray, t_obj *obj)
// {
// 	int		rgb;
// 	double	inter_bulb;
// 	t_color	color;

// 	rgb = 0;
// 	inter_bulb = has_bulb(data, ray, &color);
// 	if (inter_bulb && !is_behind_cam(inter_bulb))
// 		rgb = get_color(color.rgb[0], color.rgb[1], color.rgb[2]);
// 	if (obj->t && obj->type == O_SP && obj->ref && !inter_bulb)
// 	{
// 		get_sphere_color(&(t_get_color_params)
// 		{data, ray, obj->t, obj, &color, NULL});
// 		rgb = get_color(color.rgb[0], color.rgb[1], color.rgb[2]);
// 	}
// 	if (obj->t && obj->type == O_CY && !is_behind_cam(obj->t) && obj->ref
// 		&& !inter_bulb)
// 	{
// 		get_cylinder_color(data, ray, obj, &color);
// 		rgb = get_color(color.rgb[0], color.rgb[1], color.rgb[2]);
// 	}
// 	get_pixel_color_2(&(t_get_pixel_color_2_params){data, ray, obj, &rgb,
// 		&inter_bulb, &color});
// 	return (rgb);
// }

// /**========================================================================
//  *                           GET_PIXEL_COLOR_2
//  *========================================================================**/
// void	get_pixel_color_2(t_get_pixel_color_2_params *params)
// {
// 	t_obj	*obj;
// 	t_data	*data;
// 	t_color	*color;
// 	int		*rgb;

// 	obj = params->obj;
// 	data = params->data;
// 	color = params->color;
// 	rgb = params->rgb;
// 	if (obj->t && obj->type == O_PL && !is_behind_cam(obj->t) && obj->ref
// 		&& !*params->inter_bulb)
// 	{
// 		get_plane_color(&(t_get_color_params)
// 		{data, params->ray, obj->t, obj, color, NULL});
// 		*rgb = get_color(color->rgb[0], color->rgb[1], color->rgb[2]);
// 	}
// 	if (obj->t && obj->type == O_TR && !is_behind_cam(obj->t) && obj->ref
// 		&& !*params->inter_bulb)
// 	{
// 		get_triangle_color(&(t_get_color_params)
// 		{data, params->ray, obj->t, obj, color, NULL});
// 		*rgb = get_color(color->rgb[0], color->rgb[1], color->rgb[2]);
// 	}
// 	if (obj->ref == NULL && !*params->inter_bulb)
// 		*rgb = get_background_color(params->ray, data);
// }

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

