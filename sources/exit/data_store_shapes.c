#include "data_store.h"

void	store_and_free_spheres(t_exit *exit, void *spheres)
{
	if (exit && spheres)
		exit->spheres = (t_sphere *) spheres;
	else if (exit && exit->spheres)
	{
		free(exit->spheres);
		exit->spheres = NULL;
	}
}

void	store_and_free_cylinders(t_exit *exit, void *cylinders)
{
	if (exit && cylinders)
		exit->cylinders = (t_cylinder *) cylinders;
	else if (exit && exit->cylinders)
	{
		free(exit->cylinders);
		exit->cylinders = NULL;
	}
}

void	store_and_free_planes(t_exit *exit, void *planes)
{
	if (exit && planes)
		exit->planes = (t_plane *) planes;
	else if (exit && exit->planes)
	{
		free(exit->planes);
		exit->planes = NULL;
	}
}
