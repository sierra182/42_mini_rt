#include <stdio.h>
#include "x_mini_struct.h"


/* 

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

 */


void	print_sphere(t_sphere sphere)
{
	printf("sphere.origin_vect.axis[0]: %f\n", sphere.origin_vect.axis[0]);
	printf("sphere.origin_vect.axis[1]: %f\n", sphere.origin_vect.axis[1]);
	printf("sphere.origin_vect.axis[2]: %f\n", sphere.origin_vect.axis[2]);
	printf("sphere.diameter: %f\n", sphere.diameter);
	printf("spheres.square_radius: %f\n", sphere.square_radius);
	printf("spheres.color.rgb[0]: %i\n", sphere.color.rgb[0]);
	printf("spheres.color.rgb[1]: %i\n", sphere.color.rgb[1]);
	printf("spheres.color.rgb[2]: %i\n", sphere.color.rgb[2]);
}

void	make_rt_file(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cy_nbr)
	{
		printf(data->cylinders->)
	}

	printf("make rt file...\n");
}