/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:06:21 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:06:22 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_BONUS_H
# define EVENT_BONUS_H

# include "se_mini_struct_bonus.h"

void	get_closest_intersection_sp(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_cy(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_pl(t_data *data, t_ray *ray, t_obj *obj);
int		is_behind_cam(double t);
void	new_ray(t_cam *cam, t_ray *ray, double x, double y);

#endif