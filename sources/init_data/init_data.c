#include "x_mini_struct.h"
#include "get_next_line.h"
#include "libft.h"
#include "ft_printf.h"
# include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int	init_data(char *map_path, t_data *data)
{
	int	map_fd;
	int	i;
	char *str;
	char *token;
	bool found_camera = false;
	double	tab[20];

	ft_bzero(tab, 20);
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (0);
	while (1)
	{
		str = get_next_line(map_fd);
		if(ft_strchr(str, 'C'))
		{
			get_next_line(42);
			break ;
		}
		free (str);
	}
	token = ft_strtok(str, ", \t\n");
	i = 0;
	while (token)
	{
		token = ft_strtok(NULL, ", \t\n");
		if (token)
			tab[i] = atof(token);
		printf("tab[i]: %f\n", tab[i]);
		i++;
	}
	free(str);
	close(map_fd);
	return (1);
}
