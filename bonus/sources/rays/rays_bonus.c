#include "rays_bonus.h"

/**========================================================================
 *                           SCALE_AND_ADD_VECTORS
 *========================================================================**/
static void	scale_and_add_vectors(t_cam *cam, t_ray *ray, double norm_scale_x,
	double norm_scale_y)
{
	t_matrix_vector	scaled_up;
	t_matrix_vector	scaled_right;
	t_matrix_vector	scaled_forward;
	t_matrix_vector	sum_vect;

	scale_vector(cam->up_vect.axis, norm_scale_y, scaled_up.axis);
	scale_vector(cam->right_vect.axis, norm_scale_x, scaled_right.axis);
	scale_vector(cam->forward_vect.axis, cam->focal_len, scaled_forward.axis);
	add_vector(scaled_up.axis, scaled_right.axis, sum_vect.axis);
	add_vector(sum_vect.axis, scaled_forward.axis, ray->dir_vect.axis);
}

/**========================================================================
 *                           NORMALIZE_PIXEL
 *========================================================================**/
static double	normalize_pixel(int screen_size, double pixel, int x_flag)
{
	if (!screen_size)
		return (0.0);
	if (x_flag)
		return (((pixel) / screen_size) * 2 - 1);
	return ((1 - 2 * (pixel) / screen_size));
}

/**========================================================================
 *                           NEW_RAY
 *========================================================================**/
void	new_ray(t_cam *cam, t_ray *ray, double x, double y)
{
	double	norm_scale_x;
	double	norm_scale_y;

	cast_vector_mat_ray(&cam->origin_vect, &ray->origin_vect);
	norm_scale_y = normalize_pixel(cam->resol[1], y, 0) * cam->scale;
	norm_scale_x = normalize_pixel(cam->resol[0], x, 1) * cam->scale
		* cam->aspect;
	scale_and_add_vectors(cam, ray, norm_scale_x, norm_scale_y);
	self_normalize_vector(ray->dir_vect.axis);
}

# define THR 16
# define THR_SQRT 4
# define THR_INV_SQRT 0.25

# include <pthread.h>

typedef struct s_multy_threads
{
	t_mlx	mlx;
	t_data	*data;
	int		x_stt;
	int		x_end;
	int		y_stt;
	int		y_end;
}	t_multy_threads;

typedef struct s_launch_rays
{
	int				i;
	int				j;
	int				k;
	int				x_stt;
	int				x_end;
	int				y_stt;
	int				y_end;
	pthread_t		tids[THR];
	t_multy_threads	multy[THR];
	t_data			data_copies[THR];
}	t_launch_rays;

void	*launch_rays2(void *multy_input)
{
	t_multy_threads	*multy;
	int				x;
	int				y;

	multy = (t_multy_threads *) multy_input;
	y = multy->y_stt;
	while (++y < multy->y_end)
	{
		x = multy->x_stt;
		while (++x < multy->x_end)
		{
			if (multy->data->event.antia == 2)
				exec_launch_rays_antia(&multy->mlx, multy->data, x, y);
			if (!multy->data->event.antia)
				exec_launch_rays(&multy->mlx, multy->data, x, y);
			add_xpm_items(&multy->mlx, multy->data, x, y);
		}
	}
	return (NULL);
}


#include "libft.h"
void	copy_data(t_data *data, t_data *data_cpy)
{
	*data_cpy = *data;
	data_cpy->spheres = (t_sphere *) ft_calloc(data->sp_nbr,
			sizeof(t_sphere));
	ft_memcpy(data_cpy->spheres, data->spheres, data->sp_nbr
		* sizeof(t_sphere));
	data_cpy->cylinders = (t_cylinder *) ft_calloc(data->cy_nbr,
			sizeof(t_cylinder));
	ft_memcpy(data_cpy->cylinders, data->cylinders, data->cy_nbr
		* sizeof(t_cylinder));
	data_cpy->planes = (t_plane *) ft_calloc(data->pl_nbr,
			sizeof(t_plane));
	ft_memcpy(data_cpy->planes, data->planes, data->pl_nbr
		* sizeof(t_plane));
	data_cpy->triangles = (t_triangle *) ft_calloc(data->tr_nbr,
			sizeof(t_triangle));
	ft_memcpy(data_cpy->triangles, data->triangles, data->tr_nbr
		* sizeof(t_triangle));
	data_cpy->spotlights = (t_spotlight *) ft_calloc(data->sl_nbr,
			sizeof(t_spotlight));
	ft_memcpy(data_cpy->spotlights, data->spotlights, data->sl_nbr
		* sizeof(t_spotlight));
}
#include <stdlib.h>
void	free_data_copy(t_data *data_cpy)
{
	free(data_cpy->spheres);
	data_cpy->spheres = NULL;
	free(data_cpy->cylinders);
	data_cpy->cylinders = NULL;
	free(data_cpy->planes);
	data_cpy->planes = NULL;
	free(data_cpy->triangles);
	data_cpy->triangles = NULL;
	free(data_cpy->spotlights);
	data_cpy->spotlights = NULL;
}

void	close_launch_rays(t_mlx *mlx, t_data *data, t_launch_rays *lr)
{
	lr->i = -1;
	while (++lr->i < THR)
	{
		pthread_join(lr->tids[lr->i], NULL);
		free_data_copy(&lr->data_copies[lr->i]);
	}
	if (data->event.antia == 1)
	{
		data->event.antia = 2;
		data->refresh = 1;
	}
	else if (data->event.antia == 2)
		data->event.antia = 0;
	if (data->is_test == 1)
		make_bin_file(data, mlx);
}
/**========================================================================
 *                           LAUNCH_RAYS
 *========================================================================**/
void	launch_rays(t_mlx *mlx, t_data *data)
{
	t_launch_rays	lr;

	lr.k = 0;
	lr.i = -1;
	while (++lr.i < THR_SQRT)
	{
		lr.j = -1;
		while (++lr.j < THR_SQRT)
		{
			lr.x_stt = (WIDTH * THR_INV_SQRT * lr.j) - 1;
			lr.y_stt = (HEIGHT * THR_INV_SQRT * lr.i) - 1;
			lr.x_end = ((lr.x_stt + 1) + WIDTH * THR_INV_SQRT);
			lr.y_end = ((lr.y_stt + 1) + HEIGHT * THR_INV_SQRT);
			copy_data(data, &lr.data_copies[lr.k]);
			lr.multy[lr.k] = (t_multy_threads)
			{
				*mlx, &lr.data_copies[lr.k], lr.x_stt, lr.x_end, lr.y_stt,
				lr.y_end
			};
			pthread_create(&lr.tids[lr.k], NULL, launch_rays2,
				&lr.multy[lr.k]);
			lr.k++;
		}
	}
	close_launch_rays(mlx, data, &lr);
}

/**========================================================================
 *                           	PUT_PXL
 *========================================================================**/
void	put_pxl(t_mlx *mlx, int x, int y, unsigned int color)
{
	const double	inverse_eight = 0.125;
	int				pxl_pos;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl_pos = x * mlx->img.bpp * inverse_eight + y * mlx->img.line_len;
		*(unsigned int *)(mlx->img.img_data + pxl_pos) = color;
	}
}
