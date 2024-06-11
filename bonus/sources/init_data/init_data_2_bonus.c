#include "libft.h"

/**========================================================================
 *                           FILL_TAB
 *========================================================================**/
double	*fill_tab(char *str, double tab[])
{
	int		i;
	char	*token;

	i = 0;
	while (i < 20)
		tab[i++] = 1024;
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
