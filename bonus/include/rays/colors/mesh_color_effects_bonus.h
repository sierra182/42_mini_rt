/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_color_effects_bonus.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:51:08 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:51:09 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_COLOR_EFFECTS_BONUS_H
# define MESH_COLOR_EFFECTS_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

double	calculate_light_attenuation(t_ray_pack *light_ray, double intensity);
double	calculate_light_reflexion(t_ray *ray, t_ray_pack *light_ray,
			t_ray_vector *normal);

#endif