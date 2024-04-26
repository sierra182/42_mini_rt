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

int	main(void)
{	
	ft_printf("nique toi\n");
	t_mlx	mlx;

	mlx.connect = mlx_init();
	if (!mlx.connect)
		return (1);
	mlx.window = mlx_new_window(mlx.connect, WIDTH, HEIGHT, "fdf");
	if (!mlx.window)
		return (mlx_destroy_display(mlx.connect), free(mlx.connect), 1);	
	mlx_destroy_window(mlx->connect, mlx->window);
	mlx_destroy_display(mlx->connect);
	free(mlx->connect);
	return (0);
}