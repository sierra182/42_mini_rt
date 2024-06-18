#ifndef MOUSE_EVENTS_BONUS_H
# define MOUSE_EVENTS_BONUS_H

# include "se_mini_struct_bonus.h"

void	update_cam(t_cam *cam);
void	event_launch_rays(t_data *data, int x, int y);
void	event_spotlight_launch_rays(t_data *data, int x, int y);
#endif
