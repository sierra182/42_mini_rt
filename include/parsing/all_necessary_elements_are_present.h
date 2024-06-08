#ifndef ALL_NECESSARY_ELEMENTS_ARE_PRESENT_H
# define ALL_NECESSARY_ELEMENTS_ARE_PRESENT_H
# define FILE_SIZE 1024

# include "libft.h"
# include "se_mini_struct.h"
#include <fcntl.h>
#include <unistd.h>
#include <get_next_line.h>

int	element_is_present(char file_content[], char *el);

#endif
