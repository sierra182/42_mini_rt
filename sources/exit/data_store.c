#include "data_store.h"

void	store_and_free_mlx(t_exit *exit, void *mlx)
{
	if (exit && mlx)
		exit->mlx = (t_mlx *) mlx;
	else if (exit && exit->mlx)
	{
		mlx_destroy_window(exit->mlx->connect, exit->mlx->window);
		mlx_destroy_display(exit->mlx->connect);
		free(exit->mlx->connect);
		exit->mlx = NULL;
	}
}

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

t_mlx	*get_mlx(void)
{
	return (get_exit_struct()->mlx);
}
