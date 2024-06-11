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
	static int	j = 1;

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
				tab[i] = j;
				j++;
				printf("oh mon dieu: %s, %i\n", token, (int)tab[i]);
				data->bump_map_paths[j] = ft_strdup(token);
			}
		}
		i++;
	}
	return (tab);
}
