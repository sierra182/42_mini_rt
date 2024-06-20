#ifndef ELEMENTS_DATA_ARE_VALID_H
# define ELEMENTS_DATA_ARE_VALID_H

# include "libft.h"
# include <unistd.h>
# include "get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>

typedef enum t_num_type
{
	LTR,
	VECR,
	BYT,
	FOV,
	FL,
	UFL
}	t_num_type;

int		data_str_is_valid(char *str);
int		is_empty_str(char *str);
int		chck_fl(char *str, t_num_type num);
int		chck_bt(char *str, t_num_type num);
int		check_data(char *token, char *check);
void	free_tab(char **num);
void	free_tab(char **num);
int		is_empty_str(char *str);
int		check_data_nbrs(char *token, char	**num, int *i);

#endif