/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:38:06 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 15:38:07 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_data_2_bonus.h"

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

/**========================================================================
 *                           HANDLE_UV_MODIFS_PARAMS
 *========================================================================**/
void	handle_uv_modifs_params(t_data *data, double *nbr, char *token, int *j)
{
	*nbr = ft_atof(token);
	if (!ft_strcmp(token, "checkerboard"))
		*nbr = -42;
	if (is_valid_xpm(token))
	{
		data->bump_map_paths[*j] = ft_strdup(token);
		*nbr = (*j)++;
	}
}

/**========================================================================
 *                           ALLOC_BUMP_MAPS
 *========================================================================**/
void	alloc_bump_maps(t_data *data)
{
	int	i;
	int	j;

	data->bump_maps = (double ***)malloc(sizeof (double **) * 10);
	j = 0;
	while (j < 10)
	{
		data->bump_maps[j] = (double **)malloc(sizeof (double *) * XPM_SIZE);
		i = 0;
		while (i < XPM_SIZE)
		{
			data->bump_maps[j][i] = (double *)malloc(sizeof (double)
					* XPM_SIZE);
			i++;
		}
		j++;
	}
}
