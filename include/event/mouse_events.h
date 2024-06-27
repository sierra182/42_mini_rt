/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:48:22 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:48:23 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_EVENTS_H
# define MOUSE_EVENTS_H

# include "se_mini_struct.h"

void	event_launch_rays(t_data *data, int x, int y);
void	update_cam(t_cam *cam);

#endif