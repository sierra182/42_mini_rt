#ifndef SE_MINI_STRUCT_H
# define SE_MINI_STRUCT_H

# define WIDTH 800
# define HEIGHT 600
# define AXIS 3
# define MTX 4 
# define BIG_VALUE 100000000

# include <stdio.h>
# include "se_color_image.h"
# include "se_ray_vector.h"
# include "se_camera.h"
# include "se_geometry.h"
# include "se_general.h"
# include "se_lighting.h"
# include "se_events.h"
# include "se_exit.h"
# include "se_funcs_params.h"

typedef struct s_data
{
	int				is_gen_vid;
	int				is_test;
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
	char			img_ref[20];
}	t_data;

#endif
