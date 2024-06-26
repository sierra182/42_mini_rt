/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_exit_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:39:24 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:39:25 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SE_EXIT_BONUS_H
# define SE_EXIT_BONUS_H

# include "se_mini_struct_bonus.h"

typedef struct s_exit
{
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_plane		*planes;
	t_triangle	*triangles;
	t_spotlight	*spotlights;
	t_mlx		*mlx;
	t_data		*data_cpy;
}	t_exit;

typedef enum e_exit
{
	STT,
	MLX,
	SP,
	CY,
	PL,
	SL,
	TR,
	DATA,
	END
}	t_enum_exit;

void	add_exit_struct(void *ptr, t_enum_exit ex_en);
void	flush_exit_struct(void);

#endif