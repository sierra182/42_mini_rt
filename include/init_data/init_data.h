#ifndef INIT_DATA_H
# define INIT_DATA_H

# include "se_mini_struct.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>

void	fill_struct_a(t_data *data, double tab[]);
void	fill_struct_c(t_data *data, double tab[]);
void	fill_struct_l(t_data *data, double tab[]);
void	fill_struct_cy(t_data *data, double tab[]);
void	fill_struct_pl(t_data *data, double tab[]);
void	fill_struct_sp(t_data *data, double tab[]);
int		create_data_structs(t_data *data, char *map_path);
double	*fill_tab(char *str, double tab[]);
double	*get_element_data(char *map_path, double tab[], char *el);
int		element_is_present(char *map_path, char *el);
void	get_elements_number(t_data *data, char *map_path);
int		update_cam(t_cam *cam);
void	post_init_cam(t_cam *cam);
void	init_vars(t_data *data);

#endif