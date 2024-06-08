#include "elements_data_are_valid_utils.h"

/**========================================================================
 *                           IS_EMPTY_STR
 *========================================================================**/
int	is_empty_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\n')
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		if (str[i] == '#')
			return (1);
		i++;
	}
	return (1);
}

/**========================================================================
 *                           FREE_TAB
 *========================================================================**/
void	free_tab(char **num)
{
	int	i;

	i = 0;
	while (num[i])
		free(num[i++]);
	free(num);
}
