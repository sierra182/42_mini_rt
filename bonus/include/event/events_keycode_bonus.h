/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keycode_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:06:41 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:06:42 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_KEYCODE_BONUS_H
# define EVENTS_KEYCODE_BONUS_H

# include "se_mini_struct_bonus.h"

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);
void	rotate_cam(t_cam *cam, double angle, int axe[]);

#endif