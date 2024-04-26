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

int	loop(void *param)
{
	(void) param;
	return (0);
}

void	launch_mlx_loop(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	mlx_hook(mlx->window, 2, 1L << 0, key_press, (void *) mlx->connect);
	mlx_hook(mlx->window, 17, 0L, mlx_loop_end, mlx->connect);
	mlx_loop_hook(mlx->connect, loop, NULL);
	mlx_loop(mlx->connect);
}

int	init_mlx(void)
{
	t_mlx	mlx;

	mlx.connect = mlx_init();
	if (!mlx.connect)
		return (1);
	mlx.window = mlx_new_window(mlx.connect, WIDTH, HEIGHT, "miniRT");
	if (!mlx.window)
		return (mlx_destroy_display(mlx.connect), free(mlx.connect), 1);
	add_exit_struct(&mlx, MLX);
	return (0);
}

int	main(void)
{
	if (init_mlx())
		return (1);
	launch_mlx_loop();
	flush_exit_struct();
	return (0);
}
