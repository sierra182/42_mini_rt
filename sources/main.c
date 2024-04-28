/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:37:20 by marvin            #+#    #+#             */
/*   Updated: 2024/04/25 20:37:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	key_press(int keycode, void *param)
{
	if (keycode == 65307)
		mlx_loop_end(param);
	return (0);
}

// void	put_pxl(int x, int y, unsigned int color)
// {	
// 	char	*img_data;
// 	int		size_line;
// 	int		bpp;
// 	int		pxl_pos;

// 	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 	{		
// 		img_data_handle(NULL, &img_data, &size_line, &bpp);
// 		pxl_pos = x * bpp / 8 + y * size_line;
// 		*(unsigned int *)(img_data + pxl_pos) = color;
// 	}
// }

// static void	add_background(int x, int y)
// {
// 	char	*img_data;
// 	int		pxl_pos;
// 	int		bpp;
// 	int		size_line;

// 	img_data_handle(NULL, &img_data, &size_line, &bpp);
// 	while (++x < WIDTH)
// 	{
// 		y = -1;
// 		while (++y < HEIGHT)		
// 			put_pxl(x, y, 0xFFEDCB);		
// 	}
// }

// void	frame(t_point **pt_arr, int per, t_mlx *mlx)
// {
// 	void	*img_ptr;
// 	int		len;

// 	img_ptr = mlx_new_image(mlx->connect, WIDTH, HEIGHT);
// 	img_data_handle(img_ptr, NULL, NULL, NULL);
// 	add_background(-1, -1);
// 	mlx_put_image_to_window(mlx->connect, mlx->window, img_ptr, 0, 0);
// 	mlx_destroy_image(mlx->connect, img_ptr);
// }

// t_ray generate_ray(t_cam *cam, int pixel_x, int pixel_y)
// {
//     t_ray ray;
//     ray.origin = *(cam->origin_vect);

//     // Calcule la direction du rayon pour le pixel donné
//     // Assumons que la caméra regarde vers le 'forward' et que le plan de l'image est à une distance 'focal_len' de la caméra.
//     double aspect_ratio = (double)cam->resol[0] / cam->resol[1];
//     double scale = tan((cam->fov * 0.5) * (M_PI / 180.0));

//     double pixel_ndc_x = (pixel_x + 0.5) / cam->resol[0];
//     double pixel_ndc_y = (pixel_y + 0.5) / cam->resol[1];

//     double px = (2 * pixel_ndc_x - 1) * aspect_ratio * scale;
//     double py = (1 - 2 * pixel_ndc_y) * scale;

// 	// Calcul des composantes du vecteur direction
// 	t_vector scaled_forward = vector_scale(*(cam->forward_vect), cam->focal_len);
// 	t_vector scaled_right = vector_scale(*(cam->right_vect), px);
// 	t_vector scaled_up = vector_scale(*(cam->up_vect), py);

// 	// Addition des composantes pour obtenir le vecteur direction brut
// 	t_vector raw_direction = vector_add(vector_add(scaled_forward, scaled_right), scaled_up);

// 	// Normalisation du vecteur direction pour obtenir un vecteur unitaire
// 	ray.direction = vector_normalize(raw_direction);

//     return ray;
// }

int	loop(void)
{
	// static int	refresh;
	//(void) param;
	// refresh = (refresh + 1) % 100;	
	// if (!event->flag && refresh)
	// 	return (0);
	// frame();
	// event->flag = 0;
	return (0);
}

void	launch_mlx_loop(t_mlx *mlx)
{		
	mlx_hook(mlx->window, 2, 1L << 0, key_press, mlx->connect);
	mlx_hook(mlx->window, 17, 0L, mlx_loop_end, mlx->connect);
	mlx_loop_hook(mlx->connect, loop, NULL);
	mlx_loop(mlx->connect);
}

int	init_mlx(t_mlx *mlx)
{	
	mlx->connect = mlx_init();
	if (!mlx->connect)
		return (1);
	mlx->window = mlx_new_window(mlx->connect, WIDTH, HEIGHT, "miniRT");
	if (!mlx->window)
		return (mlx_destroy_display(mlx->connect),free(mlx->connect), 1);
	add_exit_struct((void *) mlx, MLX);
	return (0);
}

int	main(void)
{
	t_mlx	mlx;

	ft_printf("hello world!\n");	
	parse();
	if (init_mlx(&mlx))
		return (1);
	launch_mlx_loop(&mlx);
	flush_exit_struct();
	return (0);
}
