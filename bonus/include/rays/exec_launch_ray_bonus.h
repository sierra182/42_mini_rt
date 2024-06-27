/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch_ray_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:37:45 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:37:46 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_LAUNCH_RAY_BONUS_H
# define EXEC_LAUNCH_RAY_BONUS_H

# include "libft.h"
# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

void	get_pixel_color(t_get_color_params *params);
void	get_closest_intersection_sp(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_cy(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_pl(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_tr(t_data *data, t_ray *ray, t_obj *obj);
void	new_ray(t_cam *cam, t_ray *ray, double x, double y);
void	get_average_colors(t_color colors[], int n_colors,
			t_color *average);
void	apply_aces_tonemap(t_color *color);
void	calculate_ray_reflexion(t_ray *ray,	t_ray_vector *normal,
			t_ray *reflex_ray);
void	put_pxl(t_mlx *mlx, int x, int y, unsigned int color);

#endif