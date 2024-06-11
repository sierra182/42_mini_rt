#include "data_store_shapes_bonus.h"

/**========================================================================
 *                           STORE_AND_FREE_SPHERES
 *========================================================================**/
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

/**========================================================================
 *                           STORE_AND_FREE_CYLINDERS
 *========================================================================**/
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

/**========================================================================
 *                           STORE_AND_FREE_PLANES
 *========================================================================**/
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
