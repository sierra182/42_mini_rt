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
void			get_shades_nbr(int fd, int *shades_nbr, int *char_pp);
void			extract_texture_values(int shades_nbr, int char_pp, int fd,
					int int_tab[][2]);
void			fill_bump_map(t_fill_bump_map *p, int int_tab[][2]);
void			handle_line(t_handle_line_params *p, int int_tab[][2]);

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
	get_shades_nbr(fd, &shades_nbr, &char_pp);
	// printf("char_pp: %i\n", char_pp);
	extract_texture_values(shades_nbr, char_pp, fd, int_tab);
	fill_bump_map(&(t_fill_bump_map){shades_nbr, char_pp, data, fd, i}, int_tab);
	close(fd);
}

/**========================================================================
 *                           GET_SHADES_NBR
 *========================================================================**/
void	get_shades_nbr(int fd, int *shades_nbr, int *char_pp)
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
int get_char_pp_value(const char *str, int char_pp) {
    int i;
    int char_pp_value = 0;
    int factor = 1;
    
    if (str == NULL) {
        return -1;  // Error code for NULL input
    }

    i = 0;
    while (i < char_pp && str[i] != '\0') {
        char_pp_value += str[i] * factor;
        factor *= 10;
        i++;
    }

    return char_pp_value;
}

/**========================================================================
 *                           EXTRACT_TEXTURE_VALUES
 *? the logic should be modified HERE to handle the cases where their are
 *? more than 1 char to define a color... 
 *========================================================================**/
void	extract_texture_values(int shades_nbr, int char_pp,  int fd, int int_tab[][2])
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
			// printf("str_tmp: %s, ", str_tmp);
			free (str);
			str = str_tmp;
			// printf("str: %s, ", str);
			int_tab[j][0] = get_char_pp_value(str, char_pp);
			// printf("%i: ", int_tab[j][0]);
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
			if (get_char_pp_value(&p->str [*(p->j)], p->char_pp) == int_tab[k][0])
			{
				p->data->bump_maps[p->i][*(p->l)][*(p->j) / p->char_pp]
					= int_to_grayscale(int_tab[k][1]) / 255.0f;
			}
			(k)++;
		}
		(*(p->j)) += p->char_pp;
	}
	free(p->str);
}