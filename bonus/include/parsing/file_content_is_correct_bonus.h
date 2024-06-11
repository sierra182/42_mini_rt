#ifndef FILE_CONTENT_IS_CORRECT_H
# define FILE_CONTENT_IS_CORRECT_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include "se_mini_struct_bonus.h"
# include "get_next_line.h"

int	all_necessary_elements_are_present(char file_content[]);
int	elements_data_are_valid(char *map_path);
int	is_only_valid_chars(char file_content[]);
int	is_valid_char(char c);

# define FILE_SIZE 1024000

#endif