#ifndef GET_TEXTURE_BONUS_H
# define GET_TEXTURE_BONUS_H

# include "fill_struct_funcs_2_bonus.h"
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <unistd.h>
# include "libft.h"

int				gray_to_hex_string(const char *gray_string, char *hex_output);
int				hex_to_int(const char *hex_string);
void			get_texture(t_data *data, int i);
unsigned char	int_to_grayscale(unsigned int hex_value);
void			free_tab_bump(char **tab);
void			get_shades_nbr(t_sphere *sphere, int fd, int *shades_nbr,
					int *char_pp);
void			extract_texture_values(int shades_nbr, int char_pp, int fd,
					int int_tab[][2]);
void			fill_bump_map(t_fill_bump_map *p, int int_tab[][2]);
void			handle_line(t_handle_line_params *p, int int_tab[][2]);
void			handle_line(t_handle_line_params *p, int int_tab[][2]);

#endif
