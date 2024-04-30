#include "x_mini_struct.h"
#include "get_next_line.h"
#include "libft.h"
# include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

void	initialize_tab(double tab[]);


/**========================================================================
 *                             COMMENT BLOCK
 *! Tab cells initialize at -2 arbitrarily  
 *! I should probably choose another value...  
 *  
 *  
 *========================================================================**/
double	*fill_tab(char *str, double tab[])
{
	int		i;
	char	*token;

	initialize_tab(tab);
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
	char		*str;

	if (map_fd == -1)
		map_fd = open(map_path, O_RDONLY);
	while (1)
	{
		str = get_next_line(map_fd);
		if (str == NULL)
			break ;
		if(ft_strnstr(str, el, ft_strlen(el)))
		{
			tab = fill_tab(str, tab);
			free (str);
			return (tab);
		}
		free(str);
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

	while(get_element_data(map_path, tab, "A") != NULL)
		print_tab(tab, "A:\n");
	while(get_element_data(map_path, tab, "C") != NULL)
		print_tab(tab, "C:\n");
	while(get_element_data(map_path, tab, "L") != NULL)
		print_tab(tab, "L:\n");
	while(get_element_data(map_path, tab, "cy") != NULL)
		print_tab(tab, "cy :\n");
	while(get_element_data(map_path, tab, "sp") != NULL)
		print_tab(tab, "sp :\n");
	while(get_element_data(map_path, tab, "pl") != NULL)
		print_tab(tab, "pl :\n");
	return (1);
}
