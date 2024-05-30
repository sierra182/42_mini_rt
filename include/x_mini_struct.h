#ifndef X_MINI_STRUCT_H
# define X_MINI_STRUCT_H

# define WIDTH 800
# define HEIGHT 600
# define AXIS 3
# define MTX 4 
# define BIG_VALUE 100000000

# include <stdio.h>
# include "x_color_image.h"
# include "x_ray_vector.h"
# include "x_camera.h"
# include "x_geometry.h"
# include "x_general.h"
# include "x_lighting.h"
# include "x_events.h"
# include "x_exit.h"
# include "x_funcs_params.h"

typedef struct s_data
{
	int				refresh;
	int				sp_nbr;
	int				pl_nbr;
	int				cy_nbr;
	t_event			event;
	t_cam			cam;
	t_sphere		*spheres;
	t_cylinder		*cylinders;
	t_plane			*planes;
	t_spotlight		spotlight;
	t_ambiant_light	ambiant_light;
	struct s_data	*data_cpy;
}	t_data;

#endif
