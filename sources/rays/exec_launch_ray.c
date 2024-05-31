#include "rays.h"
#include "mlx.h"
#include "se_mini_struct.h"

double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
int		intersect_disc_plans(t_ray *ray, t_cylinder *cyl, t_ray_vector	*i);
double	is_intersect_cylinder(t_ray *ray, void *input_cyl, t_ray_vector *t);
int		is_behind_cam(double t);
int		get_sphere_color(t_get_color_params *params);
int		get_plane_color(t_get_color_params *params);
int		get_background_color(t_ray *ray, t_data *data);
int		get_pixel_color(t_data *data, t_ray *ray, t_obj *obj);
int		get_color(unsigned char r, unsigned char g, unsigned char b);
void	scale_vector(double vect[], double scaler, double scaled_vect[]);
void	add_vector(double a[], double b[], double sum_vect[]);
void	normalize_vector(double vector[]);
void	get_closest_intersection_sp(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_cy(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_pl(t_data *data, t_ray *ray, t_obj *obj);
void	cast_vector_mat_ray(t_matrix_vector *matrix_vect,
			t_ray_vector *ray_vect);
void	get_cylinder_color(t_data *data, t_ray *ray,
			t_obj *obj, t_color	*color);
void	new_ray(t_cam *cam, t_ray *ray, int x, int y);
void	get_pixel_color_2(t_get_pixel_color_2_params *params);

/**========================================================================
 *                           	put_pxl
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

/**========================================================================
 *                           exec_launch_rays
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
 *                           get_pixel_color
 *========================================================================**/
int	get_pixel_color(t_data *data, t_ray *ray, t_obj *obj)
{
	int		rgb;
	double	inter_bulb;
	t_color	color;

	inter_bulb = is_intersect_sphere(ray, &data->spotlight.bulb, NULL);
	if (obj->t && obj->type == O_SP && obj->ref)
	{
		get_sphere_color(&(t_get_color_params)
		{data, ray, obj->t, obj, &color});
		rgb = get_color(color.rgb[0], color.rgb[1], color.rgb[2]);
	}
	if (obj->t && obj->type == O_CY && !is_behind_cam(obj->t) && obj->ref)
	{
		get_cylinder_color(data, ray, obj, &color);
		rgb = get_color(color.rgb[0], color.rgb[1], color.rgb[2]);
	}
	get_pixel_color_2(&(t_get_pixel_color_2_params){data, ray, obj, &rgb,
		&inter_bulb, &color});
	return (rgb);
}

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
	if (obj->t && obj->type == O_PL && !is_behind_cam(obj->t) && obj->ref)
	{
		get_plane_color(&(t_get_color_params)
		{data, params->ray, obj->t, obj, color});
		*rgb = get_color(color->rgb[0], color->rgb[1], color->rgb[2]);
	}
	if (obj->ref == NULL)
		*rgb = get_background_color(params->ray, data);
	if (*params->inter_bulb && !is_behind_cam(*params->inter_bulb))
		*rgb = get_color(data->spotlight.bulb.color.rgb[0], data->spotlight
				.bulb.color.rgb[1], data->spotlight.bulb.color.rgb[2]);
}
