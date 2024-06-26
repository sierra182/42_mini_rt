/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:48:53 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 15:48:54 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	*launch_rays(void *multy_input)
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
