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


int	init_data(char *map_path, t_data *data)
{
	double	tab[20];
	int		i;

	//initialize tab
	i = 0;
	while (i < 20)
		tab[i++] = -2;




	get_element_data(map_path, tab, "A");
	printf("A:\n");
	i = 0;
		while (tab[i] != -2)
			printf("%f\n", tab[i++]);
	
	i = 0;
	while (i < 20)
		tab[i++] = -2;
	
	get_element_data(map_path, tab, "C");
	printf("C:\n");
	i = 0;
		while (tab[i] != -2)
			printf("%f\n", tab[i++]);
	
	i = 0;
	while (i < 20)
		tab[i++] = -2;
	
	get_element_data(map_path, tab, "L");
	printf("L:\n");
	i = 0;
		while (tab[i] != -2)
			printf("%f\n", tab[i++]);
	
	i = 0;
	while (i < 20)
		tab[i++] = -2;

	while(get_element_data(map_path, tab, "cy") != NULL)
	{
		i = 0;
		printf("cy %i :\n", i);
		while (tab[i] != -2)
			printf("%f\n", tab[i++]);
	}

	i = 0;
	while (i < 20)
		tab[i++] = -2;

	while(get_element_data(map_path, tab, "sp") != NULL)
	{
		i = 0;
		printf("sp %i :\n", i);
		while (tab[i] != -2)
			printf("%f\n", tab[i++]);
	}

	i = 0;
	while (i < 20)
		tab[i++] = -2;

	while(get_element_data(map_path, tab, "pl") != NULL)
	{
		i = 0;
		printf("pl %i :\n", i);
		while (tab[i] != -2)
			printf("%f\n", tab[i++]);
	}


	return (1);
}
