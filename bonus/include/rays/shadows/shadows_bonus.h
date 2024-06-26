/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:37:04 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:37:05 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADOWS_BONUS_H
# define SHADOWS_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

void	get_local_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
double	is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder,
			t_ray_vector *i);
double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
int		is_in_cylinder(t_ray_vector *normal, t_cylinder *cyl, double mesh[]);
double	is_intersect_triangle(t_ray *ray, void *input_triangle,
			t_ray_vector *i);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);

#endif