#ifndef INIT_DATA_H
# define INIT_DATA_H

# include "se_mini_struct.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include "exit.h"

void	fill_struct_a(t_data *data, double tab[]);
void	fill_struct_c(t_data *data, double tab[]);
void	fill_struct_l(t_data *data, double tab[]);
void	fill_struct_cy(t_data *data, double tab[]);
void	fill_struct_pl(t_data *data, double tab[]);
void	fill_struct_sp(t_data *data, double tab[]);
int		create_data_structs(t_data *data, char *map_path);
void	initialize_tab(double tab[]);
double	*fill_tab(char *str, double tab[]);
double	*get_element_data(char *map_path, double tab[], char *el);
void	initialize_tab(double tab[]);

#endif