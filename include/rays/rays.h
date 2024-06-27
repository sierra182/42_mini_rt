/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:54:41 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:54:42 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "se_mini_struct.h"
# include "x_linear_algebra.h"

void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y);
void	add_xpm_items(t_mlx *mlx, t_data *data, int x, int y);
void	make_bin_file(t_data *data, t_mlx *mlx);

#endif