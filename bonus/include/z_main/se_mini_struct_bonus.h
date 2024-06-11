#ifndef SE_MINI_STRUCT_H
# define SE_MINI_STRUCT_H

# define WIDTH 800
# define HEIGHT 600
# define AXIS 3
# define MTX 4 
# define BIG_VALUE 100000000

# include <stdio.h>
# include "se_color_image_bonus.h"
# include "se_ray_vector_bonus.h"
# include "se_camera_bonus.h"
# include "se_geometry_bonus.h"
# include "se_general_bonus.h"
# include "se_lighting_bonus.h"
# include "se_events_bonus.h"
# include "se_exit_bonus.h"
# include "se_funcs_params_bonus.h"

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