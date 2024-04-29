#ifndef RAYS_H
# define RAYS_H

# include <math.h>
# include "x_mini_struct.h"

void	scale_and_add_vectors(t_cam *cam, t_ray *ray, double norm_scale_x,
			double norm_scale_y);

#endif