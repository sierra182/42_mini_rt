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

// char	*get_data_str(char **str, char *el, int	map_fd)
// {
// 	while (1)
// 	{
// 		*str = get_next_line(map_fd);
// 		if(ft_strnstr(*str, el, ft_strlen(el)))
// 		{
// 			get_next_line(42);
// 			break ;
// 		}
// 		free (*str);
// 	}
// 	return (*str);
// }

double	*get_element_data_2(char *str, double tab[])
{
	int	i;
	char *token;

	token = ft_strtok(str, ", \t\n");
	i = 0;
	while (token)
	{
		token = ft_strtok(NULL, ", \t\n");
		if (token)
		{
			tab[i] = ft_atof(token);
		}
		i++;
	}
	return (tab);
}

double	*get_element_data(char *map_path, double tab[], char *el)
{
	static int	map_fd = -1;
	char *str;

	if (map_fd == -1)
		map_fd = open(map_path, O_RDONLY);
	while (1)
	{
		str = get_next_line(map_fd);
		if (str == NULL)
			break ;
		if(ft_strnstr(str, el, ft_strlen(el)))
		{
			tab = get_element_data_2(str, tab);
			free (str);
			return (tab);
		}
	}
	close(map_fd);
	map_fd = -1;
	return (NULL);
}

void	initialize_tab(double tab[])
{
	int	i;

	i = 0;
	while (i < 20)
		tab[i++] = -2;
}

void	print_tab(double tab[], char *str)
{
	int	i;

	printf("%s", str);
	i = 0;
		while (tab[i] != -2)
			printf("%f\n", tab[i++]);
}

int	init_data(char *map_path, t_data *data)
{
	double	tab[20];
	int		i;

	initialize_tab(tab);
	get_element_data(map_path, tab, "A");
	print_tab(tab, "A:\n");
	initialize_tab(tab);
	get_element_data(map_path, tab, "C");
	print_tab(tab, "C:\n");
	initialize_tab(tab);	
	get_element_data(map_path, tab, "L");
	print_tab(tab, "L:\n");
	initialize_tab(tab);
	while(get_element_data(map_path, tab, "cy") != NULL)
		print_tab(tab, "cy :\n");
	initialize_tab(tab);
	while(get_element_data(map_path, tab, "sp") != NULL)
		print_tab(tab, "sp :\n");
	initialize_tab(tab);
	while(get_element_data(map_path, tab, "pl") != NULL)
		print_tab(tab, "pl :\n");
	return (1);
}
