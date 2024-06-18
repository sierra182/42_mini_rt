#include "se_mini_struct_bonus.h"
#include <stdlib.h>

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
