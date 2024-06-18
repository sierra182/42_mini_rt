#include "data_store_bonus.h"

/**========================================================================
 *                           STORE_AND_FREE_MLX
 *========================================================================**/
void	store_and_free_mlx(t_exit *exit, void *mlx)
{
	if (exit && mlx)
		exit->mlx = (t_mlx *) mlx;
	else if (exit && exit->mlx)
	{
		mlx_destroy_image(exit->mlx->connect,
			exit->mlx->img_items.amb.img_ptr);
		mlx_destroy_image(exit->mlx->connect,
			exit->mlx->img_items.logo.img_ptr);
		mlx_destroy_image(exit->mlx->connect,
			exit->mlx->img_items.bulb.img_ptr);
		mlx_destroy_image(exit->mlx->connect,
			exit->mlx->img_items.cam.img_ptr);
		mlx_destroy_image(exit->mlx->connect,
			exit->mlx->img_items.legend.img_ptr);
		mlx_destroy_image(exit->mlx->connect,
			exit->mlx->img_items.sph.img_ptr);
		mlx_destroy_image(exit->mlx->connect,
			exit->mlx->img.img_ptr);
		mlx_destroy_window(exit->mlx->connect, exit->mlx->window);
		mlx_destroy_display(exit->mlx->connect);
		free(exit->mlx->connect);
		exit->mlx = NULL;
	}
}

/**========================================================================
 *                           STORE_AND_FREE_DATA_COPY
 *========================================================================**/
void	store_and_free_data_copy(t_exit *exit, void *data_cpy)
{
	if (exit && data_cpy)
		exit->data_cpy = (t_data *) data_cpy;
	else if (exit && exit->data_cpy)
	{
		free(exit->data_cpy->spheres);
		exit->data_cpy->spheres = NULL;
		free(exit->data_cpy->cylinders);
		exit->data_cpy->cylinders = NULL;
		free(exit->data_cpy->planes);
		exit->data_cpy->planes = NULL;
		free(exit->data_cpy->spotlights);
		exit->data_cpy->spotlights = NULL;
		free(exit->data_cpy);
		exit->data_cpy = NULL;
	}
}
