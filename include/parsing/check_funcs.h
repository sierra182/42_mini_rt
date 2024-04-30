#ifndef CHECK_FILE_H
# define CHECK_FILE_H

# include <stdlib.h>
# include "get_next_line.h"
# include <unistd.h>
# include "libft.h"
# include <fcntl.h>

typedef enum
{
	LTR,
	VECR,
	BYT,
	FOV,
	FL
}	num_type;

# define FILE_SIZE 1024

#endif