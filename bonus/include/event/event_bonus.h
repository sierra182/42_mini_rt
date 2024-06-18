#ifndef EVENT_BONUS_H
# define EVENT_BONUS_H

# include "se_mini_struct_bonus.h"

void	new_ray(t_cam *cam, t_ray *ray, int x, int y);
void	get_closest_intersection_sp(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_cy(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_pl(t_data *data, t_ray *ray, t_obj *obj);
int		is_behind_cam(double t);

#endif
