/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:06:30 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 14:06:30 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**========================================================================
 *                           MAIN
 *========================================================================**/
int	main(int argc, char **argv, char **envp)
{
	t_mlx	mlx;
	t_data	data;

	if (WIDTH < 300 || WIDTH > 1900 || HEIGHT < 300 || HEIGHT > 1900)
		return (display_error("resolution not valid\n"), 1);
	if (argc != 2)
		return (display_error("arg number not valid\n"), 1);
	if (parse(argv[1]) == 0)
		return (display_error(".rt file not valid\n"), 2);
	if (init_data(argv[1], &data) == 0)
		return (display_error("data init. error\n"), 3);
	is_it_a_test(&data, envp);
	if (generate_video_frames(&data, envp))
		return (0);
	if (init_mlx(&mlx))
		return (4);
	launch_mlx_loop(&mlx, &data);
	flush_exit_struct();
	return (0);
}

/**========================================================================
 *                           INIT_MLX
 *========================================================================**/
int	init_mlx(t_mlx *mlx)
{
	mlx->connect = mlx_init();
	if (!mlx->connect)
		return (1);
	mlx->window = mlx_new_window(mlx->connect, WIDTH, HEIGHT, "miniRT");
	if (!mlx->window)
		return (mlx_destroy_display(mlx->connect), free(mlx->connect), 1);
	mlx->img.img_ptr = mlx_new_image(mlx->connect, WIDTH, HEIGHT);
	mlx->img.img_data = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
			&mlx->img.line_len, &(int){0});
	init_img_item(mlx, &mlx->img_items.logo, "xpm/logo.xpm", 0xFF0000);
	init_img_item(mlx, &mlx->img_items.legend, "xpm/legend.xpm", 0x0);
	init_img_item(mlx, &mlx->img_items.sph, "xpm/sph.xpm", 0xFF0000);
	init_img_item(mlx, &mlx->img_items.cam, "xpm/cam.xpm", 0xFF0000);
	init_img_item(mlx, &mlx->img_items.amb, "xpm/amb.xpm", 0xFF0000);
	init_img_item(mlx, &mlx->img_items.bulb, "xpm/bulb.xpm", 0xFF0000);
	add_exit_struct((void *) mlx, MLX);
	return (0);
}

/**========================================================================
 *                           LAUNCH_MLX_LOOP
 *========================================================================**/
void	launch_mlx_loop(t_mlx *mlx, t_data *data)
{
	mlx_hook(mlx->window, 17, 0L, mlx_loop_end, mlx->connect);
	mlx_hook(mlx->window, 2, 1L << 0, key_event, (void *[]){mlx, data});
	mlx_hook(mlx->window, 3, 1L << 1, key_up_event, (void *[]){mlx, data});
	mlx_mouse_hook(mlx->window, mouse_event, (void *) data);
	mlx_hook(mlx->window, 5, 1L << 3, mouse_release, (void *) data);
	mlx_loop_hook(mlx->connect, frame, (void *[]){mlx, data});
	mlx_loop(mlx->connect);
}

/**========================================================================
 *                           INIT_IMG_ITEM
 *========================================================================**/
void	init_img_item(t_mlx *mlx, t_img *img, char *str, int color)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx->connect, str,
			&(int){0}, &(int){0});
	if (!img->img_ptr)
		return (display_error("Error loading image\n"), exit(1));
	img->img_data = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &(int){0});
	img->alpha_color = color;
}

/**========================================================================
 *                           FRAME
 *========================================================================**/
int	frame(void *param)
{
	t_mlx	*mlx;
	t_data	*data;

	mlx = (t_mlx *)((void **) param)[0];
	data = (t_data *)((void **) param)[1];
	if (!data->refresh)
		return (0);
	data->refresh = 0;
	launch_rays(mlx, data);
	mlx_put_image_to_window(mlx->connect, mlx->window, mlx->img.img_ptr, 0, 0);
	return (0);
}
