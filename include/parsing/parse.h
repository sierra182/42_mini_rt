#ifndef PARSE_H
# define PARSE_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include "se_mini_struct.h"

int	is_rt_file(char *map_path);
int	file_exists(char *map_path);
int	file_content_is_correct(t_data *data, char *map_path);

#endif