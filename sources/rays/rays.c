/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:45:00 by svidot            #+#    #+#             */
/*   Updated: 2024/05/11 18:17:56 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rays.h"

# include "mlx.h"
# include "x_mini_struct.h"
# include "x_linear_algebra.h"
# include <math.h>

double    is_intersect_plane(t_ray *ray, t_plane *plane, double *t);
double    is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder);
double	is_intersect_sphere(t_ray *ray, t_sphere *sphere);
void	exec_launch_rays(t_mlx *mlx, t_data *data, double x, double y);
void	invert_vector(double a[], double b[], double r_a[], double r_b[]);

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

void	put_pxl(t_mlx *mlx, int x, int y, unsigned int color)
{	
	const double 	inverse_eight = 0.125;
	int				pxl_pos;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{	
		pxl_pos = x *  mlx->img.bpp * inverse_eight + y * mlx->img.line_len;
		*(unsigned int *)(mlx->img.img_data + pxl_pos) = color;
	}
}

int	get_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char[])
		{r, g, b});
}

int	get_background_color(t_ray *ray)
{
	double a;

	a = 0.5 * (ray->dir_vect.axis[1] + 10.0);
    return (1.0 - a) * get_color(255, 255, 255) + a * get_color(0.5 * 255, 0.7 * 255, 1.0 * 255);
}

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector scaled_vect;	

	scale_vector(ray->dir_vect.axis, t, scaled_vect.axis);
	add_vector(ray->origin_vect.axis, scaled_vect.axis, inter_pt->axis);	
}

int		is_behind_cam(double t)
{
	return (t <= 0.0);
}

void	color_with_ambiant_light(t_color *mesh_color,
	t_ambiant_light *ambiant_light, t_color *new_color)
{
	t_color	subt_color;
	t_color	ambiant_scaled_color;
	double	tmp_color;

	scale_color(&ambiant_light->color, ambiant_light->intensity,
		&ambiant_scaled_color);
	tmp_color = ambiant_scaled_color.rgb[0] / 255.0;
	new_color->rgb[0] = tmp_color * mesh_color->rgb[0];	
	tmp_color = ambiant_scaled_color.rgb[1] / 255.0;
	new_color->rgb[1] = tmp_color * mesh_color->rgb[1];
	tmp_color = ambiant_scaled_color.rgb[2] / 255.0;
	new_color->rgb[2] = tmp_color * mesh_color->rgb[2];
}

int	is_shadow(t_ray	*light_ray, t_sphere *sphere, t_cylinder *cylinder)
{
	t_ray			opp_light_ray;

	invert_vector(light_ray->origin_vect.axis, light_ray->dir_vect.axis, 
		opp_light_ray.origin_vect.axis, opp_light_ray.dir_vect.axis);
	if (is_intersect_sphere(&opp_light_ray, sphere) > 0.0
		|| is_intersect_cylinder(&opp_light_ray, cylinder) > 0.0)
		return (1);
	return (0);	
}

void	get_sphere_color(t_ray *ray, double t,
	t_sphere *sphere, t_spotlight *spotlight, t_color *color,
	t_ambiant_light *ambiant_light)
{
	t_ray_vector	inter_pt;
	t_ray_vector	normal;
	t_ray_vector	light_ray;
	t_ray_vector	scaled_vect;
	double 			light_coef;
	t_color			subt_color;
	t_color			ambiant_color;

	get_intersect_point(ray, t, &inter_pt);
	subtract_vector(inter_pt.axis, sphere->origin_vect.axis, normal.axis);
	normalize_vector(normal.axis);
	subtract_vector(spotlight->origin_vect.axis, inter_pt.axis,
		light_ray.axis);
	normalize_vector(light_ray.axis);
	light_coef = scalar_product(light_ray.axis, normal.axis);
	light_coef = normalize_zero_one(light_coef);
	color_with_ambiant_light(&sphere->color, ambiant_light, &ambiant_color);
	subtract_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255},
		&ambiant_color, &subt_color);	
	scale_color(&subt_color, light_coef * spotlight->intensity, color);
	add_color(color, &ambiant_color, color);	
}

void	get_plane_color(t_ray *ray, double t, t_plane *plane,
	t_spotlight *spotlight, t_color *color, t_sphere *sphere,
	t_ambiant_light *ambiant_light, t_cylinder *cylinder)
{	
	t_ray_vector	normal;
	t_ray			light_ray;
	t_ray_vector	scaled_vect;
	double 			light_coef;
	t_color			subt_color;
	t_color			ambiant_color;

	cast_vector_mat_ray(&plane->norm_vect, &normal);
	get_intersect_point(ray, t, &light_ray.origin_vect);
	subtract_vector(spotlight->origin_vect.axis, light_ray.origin_vect.axis,
		light_ray.dir_vect.axis);	
	color_with_ambiant_light(&plane->color, ambiant_light, &ambiant_color);
	if (is_shadow(&light_ray, sphere, cylinder))
	{		
		*color = ambiant_color;		
		return ;
	}
	normalize_vector(light_ray.dir_vect.axis);
	light_coef = scalar_product(normal.axis, light_ray.dir_vect.axis);
	subtract_color(&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255},
		&ambiant_color, &subt_color);
	scale_color(&subt_color, light_coef * spotlight->intensity, color);
	add_color(color, &ambiant_color, color);
}

void	launch_rays(t_mlx *mlx, t_data *data)
{
	double			x;
	double			y;

	y = -1;
	while (++y < data->cam.resol[1])
	{
		x = -1;
		while (++x < data->cam.resol[0])
		{
			exec_launch_rays(mlx, data, x, y);
		}		
	}
}
