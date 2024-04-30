#include "x_mini_struct.h"
#include "get_next_line.h"
#include "libft.h"
#include "ft_printf.h"
# include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/**========================================================================
 *                             COMMENT BLOCK
 *  The solution would be to invert the relation between the funcs:
 *  instead of having get_element_data calling the GNL-loop,
 *  it's from the GNL loop that get_element_data should be called
 *  this way many elements can be extracted in one pass...
 *========================================================================**/

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

double	*get_element_data(char *map_path, double	tab[], char *el)
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
		{
			tab[i] = ft_atof(token);
			// printf("tab[i]: %f\n", tab[i]);
		}
		i++;
	}
	free(str);
	close(map_fd);
	return (tab);
}

int	init_data(char *map_path, t_data *data)
{
	double	tab[20];
	int		i;

	i = 0;
	while (i < 20)
		tab[i++] = -2;

	get_element_data(map_path, tab, "A");
	i = 0;

	while (i < 20)
		printf("%f\n", tab[i++]);
	get_element_data(map_path, tab, "C");
	i = 0;

	while (i < 20)
		printf("%f\n", tab[i++]);
	get_element_data(map_path, tab, "L");
	i = 0;

	while (i < 20)
		printf("%f\n", tab[i++]);
	return (1);
}
