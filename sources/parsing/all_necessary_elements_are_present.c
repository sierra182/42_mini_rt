#include "all_necessary_elements_are_present.h"
#include <fcntl.h>
#include <unistd.h>
#include <get_next_line.h>
/**========================================================================
 *                           all_necessary_elements_are_present
 * ! remove comment to enable element nbr check 
 *========================================================================**/
int	all_necessary_elements_are_present(t_data *data, char *map_path)
{
	if (element_is_present(map_path, "A") != 1)
		return (0);
	if (element_is_present(map_path, "C") != 1)
		return (0);
	if (element_is_present(map_path, "L") != 1)
		return (0);
	data->sp_nbr = element_is_present(map_path, "sp");
	if (data->sp_nbr == 0)
		return (0);
	data->cy_nbr = element_is_present(map_path, "cy");
	if (data->cy_nbr == 0)
		return (0);
	data->pl_nbr = element_is_present(map_path, "pl");
	if (data->pl_nbr == 0)
		return (0);
	return (1);
}

int	is_comment(char *str)
{
	int	i;
	int	yes_no;

	i = 0;
	yes_no = 0;
	while (str[i])
	{
		if (str[i] == '#')
			return (1);
		i++;
	}
	return (yes_no);
}

/**========================================================================
 *                           element_is_present
 *========================================================================**/
int	element_is_present(char *map_path, char *el)
{
	int		i;
	int		n;
	int		map_fd;
	char	*str;

	n = 0;
	map_fd = open(map_path, O_RDONLY);
	while (1)
	{
		str = get_next_line(map_fd);
		if (!str)
			break ;
		if (is_comment(str))
		{
			free(str);
			get_next_line(42);
			continue ;
		}
		n += ft_strcount(str, el);
		free(str);
	}
	close(map_fd);
	i = 0;
	return (n);
}
