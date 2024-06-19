#include "all_necessary_elements_are_present_bonus.h"

/**========================================================================
 *                           ALL_NECESSARY_ELEMENTS_ARE_PRESENT
 *========================================================================**/
int	all_necessary_elements_are_present(char *map_path)
{
	if (element_is_present(map_path, "A") != 1)
		return (0);
	if (element_is_present(map_path, "C") != 1)
		return (0);
	return (1);
}

/**========================================================================
 *                           IS_COMMENT
 *========================================================================**/
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
 *                           ELEMENT_IS_PRESENT
 *========================================================================**/
int	element_is_present(char *map_path, char *el)
{
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
	return (n);
}
