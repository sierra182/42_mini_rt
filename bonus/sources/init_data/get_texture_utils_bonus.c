/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:37:59 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 15:38:00 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_texture_utils_bonus.h"

/**========================================================================
 *                           GET_BMPATH
 *========================================================================**/
char	*get_bmpath(t_data *data, int index)
{
	return (data->bump_map_paths[index]);
}

/**========================================================================
 *                           INT_TO_RGB
 *========================================================================**/
void	int_to_rgb(unsigned int hex_value, unsigned char *r,
	unsigned char *g, unsigned char *b)
{
	*r = (hex_value >> 16) & 0xFF;
	*g = (hex_value >> 8) & 0xFF;
	*b = hex_value & 0xFF;
}

/**========================================================================
 *                           INT_TO_GRAYSCALE
 *========================================================================**/
unsigned char	int_to_grayscale(unsigned int hex_value)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	int_to_rgb(hex_value, &r, &g, &b);
	return ((unsigned char)(0.299 * r + 0.587 * g + 0.114 * b));
}

/**========================================================================
 *                           FREE_TAB_BUMP
 *========================================================================**/
void	free_tab_bump(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/**========================================================================
 *                           HANDLE_LINE
 *========================================================================**/
void	handle_line(t_handle_line_params *p, int int_tab[][2])
{
	char	*str_tmp;
	int		k;

	str_tmp = ft_substr(p->str, 1, ft_strlen(p->str) - 3);
	free (p->str);
	p->str = str_tmp;
	str_tmp = ft_strtrim(str_tmp, "\"");
	free (p->str);
	p->str = str_tmp;
	*(p->j) = 0;
	while (p->str[*(p->j)])
	{
		k = 0;
		while (k < p->shades_nbr)
		{
			if (get_char_pp_value(&p->str [*(p->j)], p->char_pp)
				== int_tab[k][0])
				p->data->bump_maps[p->i][*(p->l)][*(p->j) / p->char_pp]
					= int_tab[k][1];
			(k)++;
		}
		(*(p->j)) += p->char_pp;
	}
	free(p->str);
}
