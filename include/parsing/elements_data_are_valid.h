#ifndef ELEMENTS_DATA_ARE_VALID_H
# define ELEMENTS_DATA_ARE_VALID_H

# include "libft.h"
# include <unistd.h>
# include "get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>

int		data_str_is_valid(char *str);
int		is_empty_str(char *str);
int		check_float(char *str);
int		check_byte(char *str);
int		check_data(char *token, char *check);
void	free_tab(char **data_type);

#endif