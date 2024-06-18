#include "fill_struct_funcs_2_bonus.h"
#include <stdlib.h>
# include <fcntl.h>
#include "get_next_line.h"
# include <unistd.h>
#include "libft.h"
int gray_to_hex_string(const char *gray_string, char *hex_output);
int hex_to_int(const char *hex_string);
void get_texture(t_data *data, int i);
static void	free_tab(char **tab);
unsigned char int_to_grayscale(unsigned int hex_value);

char	*get_bmpath(t_data *data, int index)
{
	char	*bmpath;

	bmpath = data->bump_map_paths[index];
	return (bmpath);
}

void	int_to_rgb(unsigned int hex_value, unsigned char *r,
	unsigned char *g, unsigned char *b)
{
	*r = (hex_value >> 16) & 0xFF;
	*g = (hex_value >> 8) & 0xFF;
	*b = hex_value & 0xFF;
}

unsigned char	int_to_grayscale(unsigned int hex_value)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	int_to_rgb(hex_value, &r, &g, &b);
	return ((unsigned char)(0.299 * r + 0.587 * g + 0.114 * b));
}

static void	free_tab(char **tab)
{
	int i;
	int j;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void get_texture(t_data *data, int i)
{
	char *bump_map_path;
	int **texture;
	char *str;
	char *str_tmp;
	char **tab;
	int	fd;
	int	shades_nbr;
	int	char_tab[100][2];
	char hex_output[8];

	bump_map_path = data->spheres[i].bump_map_path;
	fd = open(bump_map_path, O_RDONLY);
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
			free_tab(tab);
			free(str);
			break;
		}
		free(str);
	}
	int j = 0;
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
	int k;
	int	l;
	l = 0;
	while (str)
	{
		str = get_next_line(fd);
		if (str && str[0] == '"')
		{
			str_tmp = ft_substr(str, 1, ft_strlen(str) - 3);
			free (str);
			str = str_tmp;
			str_tmp = ft_strtrim(str_tmp, "\"");
			free (str);
			str = str_tmp;
			j = 0;
			while (str[j])
			{
				k = 0;
				while (k < shades_nbr)
				{
					if (str [j] == char_tab[k][0])
					{
						data->bump_maps[i][l][j] = int_to_grayscale(char_tab[k][1]) / 255.0f;
					}
					k++;
				}
				j++;
			}
			l++;
		}
		free(str);
		j++;
	}
	close(fd);
}