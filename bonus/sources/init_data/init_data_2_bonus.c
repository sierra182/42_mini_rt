#include "libft.h"
#include <stdio.h>
#include "se_mini_struct_bonus.h"
#include <stdlib.h>

int		is_valid_xpm(char *str);
void	handle_uv_modifs_params(t_data *data, double *nbr, char *token, int *j);

/**========================================================================
 *                           FILL_TAB
 *========================================================================**/
double	*fill_tab(t_data *data, char *str, double tab[])
{
	int			i;
	char		*token;
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
			handle_uv_modifs_params(data, &(tab)[i], token, &j);
		i++;
	}
	return (tab);
}

void	handle_uv_modifs_params(t_data *data, double *nbr, char *token, int *j)
{
	*nbr = ft_atof(token);
	if (!ft_strcmp(token, "checkerboard"))
		*nbr = -42;
	if (is_valid_xpm(token))
	{
		data->bump_map_paths[*j] = ft_strdup(token);
		// printf("data->bump_map_paths[%i]: %s\n", *j, data->bump_map_paths[*j]);
		*nbr = (*j)++;
		// data->bump_map_paths[*j] = NULL;
	}
}

void	alloc_bump_maps(t_data *data)
{
	int	i;
	int	j;

	data->bump_maps = (double ***)malloc(sizeof (double **) * 10);
	j = 0;
	while (j < 10)
	{
		data->bump_maps[j] = (double **)malloc(sizeof (double *) * XPM_size);
		i = 0;
		while (i < XPM_size)
		{
			data->bump_maps[j][i] = (double *)malloc(sizeof (double) * XPM_size);
			i++;
		}
		j++;
	}
}
