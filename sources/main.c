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

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	ft_printf("hello world!\n");
	if (argc != 2)
		return (display_error(), 1);
	if (parse(argv[1]) == 0)
		return (display_error(), 2);
	if (init_mlx(&mlx))
		return (1);
	launch_mlx_loop(&mlx);
	flush_exit_struct();
	return (0);
}
