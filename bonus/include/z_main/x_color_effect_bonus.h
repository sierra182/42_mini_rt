/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_color_effect_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:40:34 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:40:49 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef X_COLOR_EFFECT_BONUS_H
# define X_COLOR_EFFECT_BONUS_H

# include "se_mini_struct_bonus.h"

double	calculate_light_attenuation(t_ray_pack *light_ray, double intensity);
void	add_self_shadowing(double light_coef, double light_attenuation,
			t_color *color);
void	add_shading( t_ray *ray, t_ray_vector *normal,
			t_color *color, t_color *res_color);
void	color_with_light(t_color *mesh_color,
			t_color *light_color, double intensity, t_color *new_color);

#endif