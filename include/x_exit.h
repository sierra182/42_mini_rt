#ifndef X_EXIT_H
# define X_EXIT_H

# include "x_mini_struct.h"

void	add_exit_struct(void *ptr, t_enum_exit ex_en);
void	flush_exit_struct(void);
t_mlx	*get_mlx(void);

#endif