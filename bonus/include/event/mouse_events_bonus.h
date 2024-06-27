/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:13:39 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:13:40 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_EVENTS_BONUS_H
# define MOUSE_EVENTS_BONUS_H

# include "se_mini_struct_bonus.h"

void	update_cam(t_cam *cam);
void	event_launch_rays(t_data *data, int x, int y);
void	event_spotlight_launch_rays(t_data *data, int x, int y);

#endif