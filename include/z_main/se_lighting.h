/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_lighting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:55:52 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:55:53 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SE_LIGHTING_H
# define SE_LIGHTING_H

typedef struct s_spotlight
{
	double			intensity;
	t_matrix_vector	origin_vect;
	t_sphere		bulb;
	t_color			color;
}	t_spotlight;

typedef struct s_ambiant_light
{
	double			intensity;
	t_color			color;
}	t_ambiant_light;

#endif