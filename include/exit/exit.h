#ifndef EXIT_H
# define EXIT_H

# include <stdlib.h>
# include "x_mini_struct.h"

typedef void	(*t_getsaf)(t_exit *, void *);
void			store_and_free_mlx(t_exit *exit, void *mlx);

#endif