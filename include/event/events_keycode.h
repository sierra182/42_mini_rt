/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keycode.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:48:11 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:48:12 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_KEYCODE_H
# define EVENTS_KEYCODE_H

# include "se_mini_struct.h"

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);
void	rotate_cam(t_cam *cam, double angle, int axe[]);

#endif