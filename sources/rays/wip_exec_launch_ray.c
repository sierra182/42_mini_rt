#include "rays.h"


# include "mlx.h"
# include "x_mini_struct.h"

//void	new_ray(t_cam *cam, t_ray *ray, int x, int y);

double	is_intersect_sphere(t_ray *ray, void *input_sphere);
double	is_intersect_plane(t_ray *ray, t_plane *plane, t_ray_vector *i);
int	intersect_disc_plans(t_ray *ray, t_cylinder *cyl, t_ray_vector	*i);
double	is_intersect_cylinder(t_ray *ray, t_cylinder *cyl);
int		is_behind_cam(double t);
void	get_sphere_color(t_ray *ray, double t, t_sphere *sphere, t_spotlight *spotlight, t_color *color, t_ambiant_light *ambiant_light);
void	get_plane_color(t_ray *ray, double t, t_plane *plane, t_spotlight *spotlight, t_color *color, t_sphere *sphere, t_ambiant_light *ambiant_light, t_cylinder *cylinder);
int	get_background_color(t_ray *ray);

void	put_pxl(t_mlx *mlx, int x, int y, unsigned int color);
int	get_color(unsigned char r, unsigned char g, unsigned char b);
void	scale_vector(double vect[], double scaler, double scaled_vect[]);
void    add_vector(double a[], double b[], double sum_vect[]);
void	normalize_vector(double vector[]);


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

void find_closest_intersection(t_intersection_params params)
{
	int		i;
	double	t;

	i = 0;
	while (i < params.obj_nbr)
	{
		//printf("out :%f\n", ((t_sphere **)params.objects)[0]->diameter);
		//printf("i :%i\n", i)
		t = params.intersect_func(&params.ray, ((t_sphere **)params.objects)[i]);
		if (t && t < params.obj->t)
		{
			params.obj->t = t;
			params.obj->type = params.obj_type;
			params.obj->ref = ((t_sphere **)params.objects)[i];
		}
		i++;
	}
	
}
#include "libft.h"
#include <stdlib.h>
void	get_closest_object(t_data *data, t_ray ray, t_obj_intersect *obj)
{
	double			t;
	int	i;
	t_intersection_params params_sp;
	t_intersection_params *params_cy;
	t_intersection_params *params_pl;
	t_sphere *sphere_addresses[1000];

	i = 0;
	while (i < data->sp_nbr)
	{
		sphere_addresses[i] = &(data->spheres[i]);
		//printf("in :%f\n", sphere_addresses[i]->diameter);
		i++;
	}
	params_sp.objects = sphere_addresses;
	//i = 0;
	//while (i < data->sp_nbr)
	//{
	//	printf("out :%f\n", ((t_sphere **)params_sp.objects)[i]->diameter);
	//	i++;
	//}

	params_sp.ray = ray;
	

	//params_sp.objects = data->spheres;
	params_sp.obj_nbr = data->sp_nbr;
	params_sp.intersect_func = is_intersect_sphere;
	params_sp.obj = obj;
	params_sp.obj_type = O_SP;

	find_closest_intersection(params_sp);
	//find_closest_intersection(params_cy);
	//find_closest_intersection(params_pl);
	//i = 0;
	//while (i < data->sp_nbr)
	//{
	//	t = is_intersect_sphere(&ray, ((t_sphere **)params_sp.objects)[i]);
	//	if (t && t < (*obj).t)
	//	{
	//		(*obj).t = t;
	//		(*obj).type = O_SP;
	//		(*obj).ref = ((t_sphere **)params_sp.objects)[i];
	//	}
	//	i++;
	//}
	i = 0;
	while (i < data->pl_nbr)
	{
		t = is_intersect_plane(&ray, &data->planes[i], NULL);
		if (t && t < (*obj).t)
		{
			(*obj).t = t;
			(*obj).type = O_PL;
			(*obj).ref = &data->planes[i];
		}
		i++;
	}
	i = 0;
	while (i < data->cy_nbr)
	{
		t = is_intersect_cylinder(&ray, &data->cylinders[i]);
		if (t && t < (*obj).t)
		{
			(*obj).t = t;
			(*obj).type = O_CY;
			(*obj).ref = &data->cylinders[i];
		}
		i++;
	}

}

void	exec_launch_rays(t_mlx *mlx, t_data *data, double x, double y)
{
	t_ray			ray;
	
	double			inter_bulb;
	t_color 		color;
	t_obj_intersect	obj;
	
	// initialize variables
	obj.t = 100000000;
	new_ray(&data->cam, &ray, x, y);
	inter_bulb = is_intersect_sphere(&ray, &data->spotlight.bulb);
	obj.ref = NULL;

	// get smallest t + obj type + obj ref
	get_closest_object(data, ray, &obj);
	// get color & display pixel
	
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
