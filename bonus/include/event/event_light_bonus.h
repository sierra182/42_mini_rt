/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_light_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:06:29 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:06:30 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_LIGHT_BONUS_H
# define EVENT_LIGHT_BONUS_H

# include "se_mini_struct_bonus.h"

void	new_ray(t_cam *cam, t_ray *ray, double x, double y);
double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
int		is_behind_cam(double t);

#endif