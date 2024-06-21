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
void			free_tab_bump(char **tab);
void			get_shades_nbr(int fd, int *shades_nbr);
void			extract_texture_values(int shades_nbr, int fd,
					int int_tab[][2]);
void			fill_bump_map(t_fill_bump_map *p, int int_tab[][2]);

/**========================================================================
 *                           GET_TEXTURE
 *========================================================================**/
void	get_texture(t_data *data, int i)
{
	int	fd;
	int	shades_nbr;
	int	char_pp;
	int	int_tab[100][2];

	fd = open(data->spheres[i].bump_map_path, O_RDONLY);
	get_shades_nbr(fd, &shades_nbr);
	extract_texture_values(shades_nbr, fd, int_tab);
	fill_bump_map(&(t_fill_bump_map){shades_nbr, data, fd, i}, int_tab);
	close(fd);
}

/**========================================================================
 *                           GET_SHADES_NBR
 *========================================================================**/
void	get_shades_nbr(int fd, int *shades_nbr)
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
			free_tab_bump(tab);
			free(str);
			break ;
		}
		free(str);
	}
}

/**========================================================================
 *                           EXTRACT_TEXTURE_VALUES
 *? the logic should be modified HERE to handle the cases where their are
 *? more than 1 char to define a color... 
 *========================================================================**/
void	extract_texture_values(int shades_nbr, int fd, int int_tab[][2])
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
			int_tab[j][0] = str[0];
			if (gray_to_hex_string(&str[4], hex_output))
				int_tab[j][1] = hex_to_int(hex_output);
			else
				int_tab[j][1] = hex_to_int(&str[4]);
		}
		free(str);
		j++;
	}
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
			if (p->str [*(p->j)] == int_tab[k][0])
				p->data->bump_maps[p->i][*(p->l)][*(p->j)]
					= int_to_grayscale(int_tab[k][1]) / 255.0f;
			(k)++;
		}
		(*(p->j))++;
	}
	free(p->str);
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
			{p->data, str, &j, p->i, p->shades_nbr, &l}, int_tab);
			l++;
		}
		else
			free(str);
		j++;
	}
}
