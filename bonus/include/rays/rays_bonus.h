#ifndef RAYS_BONUS_H
# define RAYS_BONUS_H

# include <pthread.h>
# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y);
void	exec_launch_rays_antia(t_mlx *mlx, t_data *data, int x, int y);
void	add_xpm_items(t_mlx *mlx, t_data *data, int x, int y);
void	make_bin_file(t_data *data, t_mlx *mlx);

#endif
