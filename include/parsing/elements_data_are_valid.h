#ifndef ELEMENTS_DATA_ARE_VALID_H
# define ELEMENTS_DATA_ARE_VALID_H

# include "libft.h"
# include <unistd.h>
# include "get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>

typedef enum
{
	LTR,
	VECR,
	BYT,
	FOV,
	FL
}	num_type;

int		data_str_is_valid(char *str);
int		is_empty_str(char *str);
int		chck_fl(char *str, num_type);
int		check_byte(char *str);
int		check_data(char *token, char *check);
void	free_tab(char **num);

#endif