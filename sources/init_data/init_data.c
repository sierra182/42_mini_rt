#include "x_mini_struct.h"
#include "get_next_line.h"
#include "libft.h"
#include "ft_printf.h"
# include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


char	*get_data_str(char **str, char *el, int	map_fd)
{
	while (1)
	{
		*str = get_next_line(map_fd);
		if(ft_strnstr(*str, el, ft_strlen(el)))
		{
			get_next_line(42);
			break ;
		}
		free (*str);
	}
	return (*str);
}

int	get_element_data(char *map_path, double	tab[], char *el)
{
	int	map_fd;
	int	i;
	char *str;
	char *token;
	bool found_camera = false;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (0);
	get_data_str(&str, el, map_fd);
	// ft_printf("%s", str);
	token = ft_strtok(str, ", \t\n");
	i = 0;
	while (token)
	{
		token = ft_strtok(NULL, ", \t\n");
		if (token)
			tab[i] = ft_atof(token);
		// printf("tab[i]: %f\n", tab[i]);
		i++;
	}
	free(str);
	close(map_fd);
	return (1);
}

int	init_data(char *map_path, t_data *data)
{
	double	tab[20];

	ft_bzero(tab, 20);

	if (get_element_data(map_path, tab, "C") == 0)
		return (0);
	return (1);
}
