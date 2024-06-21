#ifndef EXEC_LAUNCH_RAY_BONUS_H
# define EXEC_LAUNCH_RAY_BONUS_H

# include "se_mini_struct_bonus.h"

double		is_intersect_sphere(t_ray *ray, void *input_sphere,
				t_ray_vector *i);
double		is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
int			intersect_disc_plans(t_ray *ray, t_cylinder *cyl,
				t_ray_vector	*i);
double		is_intersect_cylinder(t_ray *ray, void *input_cyl,
				t_ray_vector *t);
int			is_behind_cam(double t);
void		get_sphere_color(t_get_color_params *params);
void		get_plane_color(t_get_color_params *params);
void		get_background_color(t_ray *ray, t_data *data,
				t_color *back_color);
static void	get_pixel_color(t_data *data, t_ray *ray, t_obj *obj,
				t_color *color, t_ray_vector *normal, t_ray_pack *light_ray);
int			get_color(unsigned char r, unsigned char g, unsigned char b);
void		get_closest_intersection_sp(t_data *data, t_ray *ray, t_obj *obj);
void		get_closest_intersection_cy(t_data *data, t_ray *ray, t_obj *obj);
void		get_closest_intersection_pl(t_data *data, t_ray *ray, t_obj *obj);
void		get_cylinder_color(t_data *data, t_ray *ray,
				t_obj *obj, t_color	*color, t_ray_vector *normal, t_ray_pack *light_ray);
void		put_pxl(t_mlx *mlx, int x, int y, unsigned int color);
void		get_closest_intersection_tr(t_data *data, t_ray *ray, t_obj *obj);
double		is_intersect_triangle(t_ray *ray, void *input_triangle,
				t_ray_vector *i);
void		get_triangle_color(t_get_color_params *params);
void		new_ray(t_cam *cam, t_ray *ray, double x, double y);
void		get_average_colors(t_color colors[], int n_colors,
				t_color *average);

#endif
