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

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"
#include "mlx.h"

#define WIDTH 600
#define HEIGHT 500

typedef struct s_mlx
{
	void	*connect;
	void	*window;
}	t_mlx;

int	key_press(int keycode, void *param)
{
	// t_event	*event;

	// event = (t_event *) param[1];
	if (keycode == 65307)
		mlx_loop_end(param);
	return (0);
}

int	loop(void *param)
{
	(void) param;
	return (0);
}

int	main(void)
{	
	t_mlx	mlx;

	mlx.connect = mlx_init();
	if (!mlx.connect)
		return (1);
	mlx.window = mlx_new_window(mlx.connect, WIDTH, HEIGHT, "miniRT");
	if (!mlx.window)
		return (mlx_destroy_display(mlx.connect), free(mlx.connect), 1);
	mlx_hook(mlx.window, 2, 1L << 0, key_press, (void *) mlx.connect);
	mlx_hook(mlx.window, 17, 0L, mlx_loop_end, mlx.connect);
	mlx_loop_hook(mlx.connect, loop, NULL);
	mlx_loop(mlx.connect);
	mlx_destroy_window(mlx.connect, mlx.window);
	mlx_destroy_display(mlx.connect);
	free(mlx.connect);
	return (0);
}