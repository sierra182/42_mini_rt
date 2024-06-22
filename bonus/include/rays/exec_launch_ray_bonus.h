#ifndef EXEC_LAUNCH_RAY_BONUS_H
# define EXEC_LAUNCH_RAY_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

void	get_pixel_color(t_get_color_params *params);
void	get_closest_intersection_sp(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_cy(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_pl(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_tr(t_data *data, t_ray *ray, t_obj *obj);
void	put_pxl(t_mlx *mlx, int x, int y, unsigned int color);
void	new_ray(t_cam *cam, t_ray *ray, double x, double y);
void	get_average_colors(t_color colors[], int n_colors,
			t_color *average);
void	apply_aces_tonemap(t_color *color);

#endif
