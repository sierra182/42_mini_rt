#include "rays.h"


# include "mlx.h"
# include "x_mini_struct.h"

//void	new_ray(t_cam *cam, t_ray *ray, int x, int y);

double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
int	intersect_disc_plans(t_ray *ray, t_cylinder *cyl, t_ray_vector	*i);
double	is_intersect_cylinder(t_ray *ray, void *input_cyl, t_ray_vector *t);
int		is_behind_cam(double t);
void	get_sphere_color(t_ray *ray, double t, t_sphere *sphere, t_spotlight *spotlight, t_color *color, t_ambiant_light *ambiant_light);
void	get_plane_color(t_ray *ray, double t, t_plane *plane, t_spotlight *spotlight, t_color *color, t_sphere *sphere, t_ambiant_light *ambiant_light, t_cylinder *cylinder);
int	get_background_color(t_ray *ray);

void	put_pxl(t_mlx *mlx, int x, int y, unsigned int color);
int	get_color(unsigned char r, unsigned char g, unsigned char b);
void	scale_vector(double vect[], double scaler, double scaled_vect[]);
void    add_vector(double a[], double b[], double sum_vect[]);
void	normalize_vector(double vector[]);
void	get_closest_intersection_sp(t_data *data, t_ray ray, t_obj_intersect *obj);
void	get_closest_intersection_cy(t_data *data, t_ray ray, t_obj_intersect *obj);
void	get_closest_intersection_pl(t_data *data, t_ray ray, t_obj_intersect *obj);

void	cast_vector_mat_ray(t_matrix_vector *matrix_vect, t_ray_vector *ray_vect);



static void	scale_and_add_vectors(t_cam *cam, t_ray *ray, double norm_scale_x,
	double norm_scale_y)
{
	t_matrix_vector	scaled_up;
	t_matrix_vector	scaled_right;
	t_matrix_vector	scaled_forward;
	t_matrix_vector	sum_vect;

	scale_vector(cam->up_vect.axis, norm_scale_y, scaled_up.axis);
	scale_vector(cam->right_vect.axis, norm_scale_x, scaled_right.axis);
	scale_vector(cam->forward_vect.axis, cam->focal_len, scaled_forward.axis);
	add_vector(scaled_up.axis, scaled_right.axis, sum_vect.axis);
	add_vector(sum_vect.axis, scaled_forward.axis, ray->dir_vect.axis);
}

static double	normalize_pixel(int screen_size, int pixel, int x_flag)
{
	if (!screen_size)
		return (0.0);
	if (x_flag)
		return (((pixel + 0.5) / screen_size) * 2 - 1);
	return ((1 - 2 * (pixel + 0.5) / screen_size));
}

static void	new_ray(t_cam *cam, t_ray *ray, int x, int y)
{
	double		norm_scale_x;
	double		norm_scale_y;

	cast_vector_mat_ray(&cam->origin_vect, &ray->origin_vect);
	norm_scale_y = normalize_pixel(cam->resol[1], y, 0) * cam->scale;
	norm_scale_x = normalize_pixel(cam->resol[0], x, 1) * cam->scale
		* cam->aspect;
	scale_and_add_vectors(cam, ray, norm_scale_x, norm_scale_y);
	normalize_vector(ray->dir_vect.axis);
}

void		get_pixel_color(t_data *data, t_ray ray, t_obj_intersect obj, t_color color)
{

	
}


/* 
	je suis en train de refactoriser la fonciton exec_launch_rays.
	prochaine etape: get_pixel_color!

 */

void	exec_launch_rays(t_mlx *mlx, t_data *data, double x, double y)
{
	t_ray			ray;
	double			inter_bulb;
	t_color 		color;
	t_obj_intersect	obj;
	
	new_ray(&data->cam, &ray, x, y);
	inter_bulb = is_intersect_sphere(&ray, &data->spotlight.bulb, NULL);
	obj.t = 100000000;
	obj.ref = NULL;

	get_closest_intersection_sp(data, ray, &obj);
	get_closest_intersection_cy(data, ray, &obj);
	get_closest_intersection_pl(data, ray, &obj);
	get_pixel_color(data, ray, obj, color);

	
	if (obj.t && obj.type == O_SP && !is_behind_cam(obj.t) && obj.ref)
	{
		get_sphere_color(&ray, obj.t, obj.ref, &data->spotlight, &color,  &data->ambiant_light);
		put_pxl(mlx, x, y, get_color(color.rgb[0], color.rgb[1], color.rgb[2]));
	}
	if (obj.t && obj.type == O_CY && !is_behind_cam(obj.t) && obj.ref)
	{
		put_pxl(mlx, x, y, get_color(0,255,255));
	}
	if (obj.t && obj.type == O_PL && !is_behind_cam(obj.t) && obj.ref)
	{
		get_plane_color(&ray, obj.t, obj.ref, &data->spotlight, &color, &data->spheres[0], &data->ambiant_light, &data->cylinders[0]);
		put_pxl(mlx, x, y, get_color(color.rgb[0], color.rgb[1], color.rgb[2]));
	}
	if (inter_bulb && !is_behind_cam(inter_bulb))
		put_pxl(mlx, x, y, get_color(data->spotlight.bulb.color.rgb[0], data->spotlight.bulb.color.rgb[1], data->spotlight.bulb.color.rgb[2]));
	if (obj.ref == NULL)
		put_pxl(mlx, x, y, get_background_color(&ray));	
}
