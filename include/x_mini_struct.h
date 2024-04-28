/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_mini_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:43:47 by svidot            #+#    #+#             */
/*   Updated: 2024/04/28 21:16:56 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef X_MINI_STRUCT_H
# define X_MINI_STRUCT_H

# define WIDTH 600
# define HEIGHT 500
# define AXIS 3

typedef struct s_mlx
{
	void	*connect;
	void	*window;
}	t_mlx;

typedef struct s_vector
{
	double	axis[AXIS];
}	t_vector;

typedef struct s_ray
{
    t_vector	*origin_vect;
    t_vector	*dir_vect;
}	t_ray;

typedef struct s_cam
{
	double		fov;
	double		focal_len;
	int			resol[2];	
	t_vector	*origin_vect;
	t_vector	*up_vect;
	t_vector	*forward_vect;
	t_vector	*right_vect;
}	t_cam;

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