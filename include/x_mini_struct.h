/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_mini_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:43:47 by svidot            #+#    #+#             */
/*   Updated: 2024/04/26 17:03:17 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef X_MINI_STRUCT_H
# define X_MINI_STRUCT_H

# define WIDTH 600
# define HEIGHT 500

typedef struct s_mlx
{
	void	*connect;
	void	*window;
}	t_mlx;

typedef struct s_exit
{
	t_mlx	*mlx;
}	t_exit;

typedef enum e_exit
{
	STT,
	MLX,
	END
}	t_enum_exit;

#endif