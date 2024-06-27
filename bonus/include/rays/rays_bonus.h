/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:38:22 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:38:23 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_BONUS_H
# define RAYS_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y);
void	exec_launch_rays_antia(t_mlx *mlx, t_data *data, int x, int y);
void	add_xpm_items(t_mlx *mlx, t_data *data, int x, int y);

#endif