#include "exec_launch_ray_bonus.h"


void	get_average_colors(t_color colors[], int n_colors, t_color *average);
/**========================================================================
 *                           EXEC_LAUNCH_RAYS
 *========================================================================**/
void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y)
{
	t_ray	ray;
	t_obj	obj;
	t_color	color;

	new_ray(&data->cam, &ray, x + 0.5f, y + 0.5f);
	obj.t = BIG_VALUE;
	obj.ref = NULL;
	obj.type = 5;
	get_closest_intersection_sp(data, &ray, &obj);
	get_closest_intersection_cy(data, &ray, &obj);
	get_closest_intersection_pl(data, &ray, &obj);
	get_closest_intersection_tr(data, &ray, &obj);
	get_pixel_color(data, &ray, &obj, &color);
	put_pxl(mlx, x, y, get_color(color.rgb[0], color.rgb[1], color.rgb[2]));
}

/**========================================================================
 *                         EXEC_LAUNCH_RAYS_ANTIA
 *========================================================================**/
void	exec_launch_rays_antia(t_mlx *mlx, t_data *data, int x, int y)
{
	double alia = 4.0;
	int		i;
	int		j;
	t_ray	ray;
	t_obj	obj;
	t_color	colors[16];
	t_color	average_color;

	double ax, ay, xx;

	ay = y + 0.5f / alia;
	xx = x + 0.5f / alia;	
	int k = 0;
	i = -1;
	while (++i < alia)
	{
		j = -1;
		ax = xx;		
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
			k++;
		}
		ay += 1.0f / alia;	
	}
	get_average_colors(colors, 16, &average_color);
	//   printf("%d, %d, %d\n", average_color.rgb[0], average_color.rgb[1], average_color.rgb[2]);

	put_pxl(mlx, x, y, get_color(average_color.rgb[0], average_color.rgb[1], average_color.rgb[2]));
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
void	get_pixel_color(t_data *data, t_ray *ray, t_obj *obj, t_color *color)
{
	double	inter_bulb;

	inter_bulb = has_bulb(data, ray, color);
	if (obj->t && obj->type == O_SP && obj->ref && !inter_bulb)	
		get_sphere_color(&(t_get_color_params)
		{data, ray, obj->t, obj, color, NULL});	
	if (obj->t && obj->type == O_CY && !is_behind_cam(obj->t) && obj->ref
		&& !inter_bulb)	
		get_cylinder_color(data, ray, obj, color);	
	if (obj->t && obj->type == O_PL && !is_behind_cam(obj->t) && obj->ref
		&& !inter_bulb)	
		get_plane_color(&(t_get_color_params)
		{data, ray, obj->t, obj, color, NULL});	
	if (obj->t && obj->type == O_TR && !is_behind_cam(obj->t) && obj->ref
		&& !inter_bulb)	
		get_triangle_color(&(t_get_color_params)
		{data, ray, obj->t, obj, color, NULL});		
	if (obj->ref == NULL && !inter_bulb)
		get_background_color(ray, data, color);
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

