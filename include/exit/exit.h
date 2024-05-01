#ifndef EXIT_H
# define EXIT_H

# include <stdlib.h>
# include "x_mini_struct.h"

typedef void	(*t_getsaf)(t_exit *, void *);
void			store_and_free_mlx(t_exit *exit, void *mlx);
void			store_and_free_spheres(t_exit *exit, void *spheres);
void			store_and_free_cylinders(t_exit *exit, void *cylinders);
void			store_and_free_planes(t_exit *exit, void *planes);

#endif