#include "x_mini_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include "x_exit.h"

int	create_data_structs(t_data *data, char *map_path)
{
	int		nbr;
	int		i;

	data->spheres = (t_sphere *)malloc(sizeof(t_sphere) * data->sp_nbr);
	if (data->spheres == NULL)
		return (0);
	add_exit_struct(data->spheres, SP);
	data->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder) * data->cy_nbr);
	if (data->cylinders == NULL)
		return (0);
	add_exit_struct(data->cylinders, CY);
	data->planes = (t_plane *)malloc(sizeof(t_plane) * data->pl_nbr);
	if (data->planes == NULL)
		return (0);
	add_exit_struct(data->planes, PL);
	return (1);
}
