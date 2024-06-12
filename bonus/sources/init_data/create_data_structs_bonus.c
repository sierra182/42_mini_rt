#include "create_data_structs_bonus.h"

/**========================================================================
 *                           CREATE_DATA_STRUCTS
 *========================================================================**/
int	create_data_structs(t_data *data)
{
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
	data->spotlights = (t_spotlight *)malloc(sizeof(t_spotlight) * data->sl_nbr);
	if (data->spotlights == NULL)
		return (0);
	else 
		printf("%i spotlights were malloc'd\n", data->sl_nbr);
	add_exit_struct(data->spotlights, SL);
	return (1);
}
