# include "x_mini_struct.h"
# include "libft.h"

void	calculate_missing_vectors(t_cam *cam);

/**========================================================================
 *                           RESET
 *========================================================================**/
void	reset(t_data *data)
{
	t_reset_tmps tmps;

	tmps.planes = data->planes;
	tmps.spheres = data->spheres;
	tmps.cylinders = data->cylinders;
	tmps.data_cpy = data->data_cpy;
	tmps.planes_cpy = data->data_cpy->planes;
	tmps.spheres_cpy = data->data_cpy->spheres;
	tmps.cylinders_cpy = data->data_cpy->cylinders;
	*data = *data->data_cpy;
	data->planes = tmps.planes;
	data->spheres = tmps.spheres;
	data->cylinders = tmps.cylinders;
	data->data_cpy = tmps.data_cpy;	
	ft_memcpy(data->planes, tmps.planes_cpy, data->pl_nbr *
		sizeof(t_plane));
	ft_memcpy(data->spheres, tmps.spheres_cpy, data->sp_nbr *
		sizeof(t_sphere));
	ft_memcpy(data->cylinders, tmps.cylinders_cpy, data->cy_nbr *
		sizeof(t_cylinder));
}

/**========================================================================
 *                           RESET_CAM
 *========================================================================**/
void	reset_cam(t_data *data)
{
	data->cam.forward_vect.axis[1] = 0;
	calculate_missing_vectors(&data->cam);
}