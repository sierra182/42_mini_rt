#include "libft.h"
#include <stdio.h>
#include "se_mini_struct_bonus.h"
int	is_valid_png(char *str);
/**========================================================================
 *                           FILL_TAB
 *========================================================================**/
double	*fill_tab(t_data *data, char *str, double tab[])
{
	int		i;
	char	*token;
	static int	j = 0;

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
			if (!ft_strcmp(token, "checkerboard"))
				tab[i] = -42;
			if (is_valid_png(token))
			{
				// printf("token: %s\n", token);
				data->bump_map_paths[j] = ft_strdup(token);
				tab[i] = j++;
				data->bump_map_paths[j] = NULL;
			}
		}
		i++;
	}
	return (tab);
}
