#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include "ft_printf.h"
# include "x_exit.h"
# include "libft.h"
# include "mlx.h"

void	display_error(char *error);
int		parse(t_data *data, char *map_path);
void	launch_rays(t_mlx *mlx, t_data *data);

#endif