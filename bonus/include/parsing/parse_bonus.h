#ifndef PARSE_H
# define PARSE_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include "se_mini_struct_bonus.h"

int	is_rt_file(char *map_path);
int	file_exists(char *map_path);
int	file_content_is_correct(char *map_path);

#endif