#include "fill_struct_funcs_2_bonus.h"
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <unistd.h>
#include "libft.h"

int				gray_to_hex_string(const char *gray_string, char *hex_output);
int				hex_to_int(const char *hex_string);
void			get_texture(t_data *data, int i);
unsigned char	int_to_grayscale(unsigned int hex_value);
void	free_tab_bump(char **tab);

int	get_shades_nbr(int fd, char **tab)
{
	char	*str_tmp;
	int		shades_nbr;
	char	*str;

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
			shades_nbr = ft_atoi(tab[2]);
			free_tab_bump(tab);
			free(str);
			break ;
		}
		free(str);
	}
	return (shades_nbr);
}

void	extract_texture_values(int shades_nbr, int fd, int char_tab[][2])
{
	char	hex_output[8];
	int		j;
	char	*str_tmp;
	char	*str;

	j = 0;
	while (j < shades_nbr)
	{
		str = get_next_line(fd);
		if (str && str[0] == '"')
		{
			str_tmp = ft_substr(str, 1, ft_strlen(str) - 4);
			free (str);
			str = str_tmp;
			char_tab[j][0] = str[0];
			if (gray_to_hex_string(&str[4], hex_output))
				char_tab[j][1] = hex_to_int(hex_output);
			else
				char_tab[j][1] = hex_to_int(&str[4]);
		}
		free(str);
		j++;
	}
}

void	handle_line(t_data *data, char *str, int *j, int i,
	int shades_nbr, int *l, int char_tab[][2])
{
	char	*str_tmp;
	int		k;

	str_tmp = ft_substr(str, 1, ft_strlen(str) - 3);
	free (str);
	str = str_tmp;
	str_tmp = ft_strtrim(str_tmp, "\"");
	free (str);
	str = str_tmp;
	*j = 0;
	while (str[*j])
	{
		k = 0;
		while (k < shades_nbr)
		{
			if (str [*j] == char_tab[k][0])
				data->bump_maps[i][*l][*j]
					= int_to_grayscale(char_tab[k][1]) / 255.0f;
			k++;
		}
		(*j)++;
	}
}

/**========================================================================
 *                           FILL_BUMP_MAP
 *========================================================================**/
void	fill_bump_map(int shades_nbr, int char_tab[][2],
	t_data *data, int fd, int i)
{
	int		j;
	int		l;
	char	*str;

	l = 0;
	while (str)
	{
		str = get_next_line(fd);
		if (str && str[0] == '"')
		{
			handle_line(data, str, &j, i, shades_nbr, &l, char_tab);
			l++;
		}
		free(str);
		j++;
	}
}

void	get_texture(t_data *data, int i)
{
	char	*str_tmp;
	char	**tab;
	int		fd;
	int		shades_nbr;
	int		char_tab[100][2];

	fd = open(data->spheres[i].bump_map_path, O_RDONLY);
	shades_nbr = get_shades_nbr(fd, tab);
	extract_texture_values(shades_nbr, fd, char_tab);
	fill_bump_map(shades_nbr, char_tab, data, fd, i);
	close(fd);
}
