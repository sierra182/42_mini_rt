/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_color_effects.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:52:15 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:52:16 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_COLOR_EFFECTS_H
# define MESH_COLOR_EFFECTS_H

# include "se_mini_struct.h"
# include "x_linear_algebra.h"

double	calculate_light_attenuation(t_ray_pack *light_ray, double intensity);

#endif