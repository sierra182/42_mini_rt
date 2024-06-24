#include "get_texture_bonus.h"

/**========================================================================
 *                           GET_TEXTURE
 *========================================================================**/
void	get_texture(t_data *data, int i)
{
	int	fd;
	int	shades_nbr;
	int	char_pp;
	int	int_tab[500][2];

	fd = open(data->spheres[i].bump_map_path, O_RDONLY);
	get_shades_nbr(&data->spheres[i], fd, &shades_nbr, &char_pp);
	extract_texture_values(shades_nbr, char_pp, fd, int_tab);
	fill_bump_map(&(t_fill_bump_map)
	{shades_nbr, char_pp, data, fd, i}, int_tab);
	close(fd);
}

/**========================================================================
 *                           GET_SHADES_NBR
 *========================================================================**/
void	get_shades_nbr(t_sphere *sphere, int fd, int *shades_nbr, int *char_pp)
{
	char	*str;
	char	*str_tmp;
	char	**tab;

	str = "";
	while (str)
	{
		str = get_next_line(fd);
		if (str && str[0] == '"')
		{
			str_tmp = ft_substr(str, 1, ft_strlen(str) - 5);
			free(str);
			str = str_tmp;
			tab = ft_split(str, ' ');
			*shades_nbr = ft_atoi(tab[2]);
			*char_pp = ft_atoi(tab[3]);
			sphere->xpm_size_x = ft_atoi(tab[0]);
			sphere->xpm_size_y = ft_atoi(tab[1]);
			free_tab_bump(tab);
			free(str);
			break ;
		}
		free(str);
	}
}

/**========================================================================
 *                           GET_CHAR_PP_VALUE
 *========================================================================**/
int	get_char_pp_value(const char *str, int char_pp)
{
	int	i;
	int	char_pp_value;
	int	factor;

	char_pp_value = 0;
	factor = 1;
	if (str == NULL)
		return (-1);
	i = 0;
	while (i < char_pp && str[i] != '\0')
	{
		char_pp_value += str[i] * factor;
		factor *= 10;
		i++;
	}
	return (char_pp_value);
}

/**========================================================================
 *                           EXTRACT_TEXTURE_VALUES
 *? the logic should be modified HERE to handle the cases where their are
*? more than 1 char to define a color... 
*========================================================================**/
void	extract_texture_values(int shades_nbr, int char_pp, int fd,
	int int_tab[][2])
{
	char	*str;
	char	*str_tmp;
	char	hex_output[8];
	int		j;

	j = 0;
	while (j < shades_nbr)
	{
		str = get_next_line(fd);
		if (str && str[0] == '"')
		{
			str_tmp = ft_substr(str, 1, ft_strlen(str) - 4);
			free (str);
			str = str_tmp;
			int_tab[j][0] = get_char_pp_value(str, char_pp);
			if (gray_to_hex_string(&str[3 + char_pp], hex_output))
				int_tab[j][1] = hex_to_int(hex_output);
			else
				int_tab[j][1] = hex_to_int(&str[3 + char_pp]);
		}
		free(str);
		j++;
	}
}

/**========================================================================
 *                           FILL_BUMP_MAP
 *========================================================================**/
void	fill_bump_map(t_fill_bump_map *p, int int_tab[][2])
{
	int		j;
	int		l;
	char	*str;

	l = 0;
	str = "";
	while (str)
	{
		str = get_next_line(p->fd);
		if (str && str[0] == '"')
		{
			handle_line(&(t_handle_line_params)
			{p->data, str, &j, p->i, p->shades_nbr, p->char_pp, &l}, int_tab);
			l++;
		}
		else
			free(str);
		j++;
	}
}
