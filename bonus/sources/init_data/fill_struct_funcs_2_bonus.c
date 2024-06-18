#include "fill_struct_funcs_2_bonus.h"
#include <stdlib.h>
# include <fcntl.h>
#include "get_next_line.h"
# include <unistd.h>
#include "libft.h"
int gray_to_hex_string(const char *gray_string, char *hex_output);
int hex_to_int(const char *hex_string);

char *get_bmpath(t_data *data, int index)
{
	char *bmpath;

	bmpath = data->bump_map_paths[index];
	return bmpath;
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

void int_to_rgb(unsigned int hex_value, unsigned char *r, unsigned char *g, unsigned char *b)
{
	*r = (hex_value >> 16) & 0xFF;
	*g = (hex_value >> 8) & 0xFF;
	*b = hex_value & 0xFF;
}

unsigned char int_to_grayscale(unsigned int hex_value)
{
	unsigned char r, g, b;
	int_to_rgb(hex_value, &r, &g, &b);
	return (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
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
	// printf("bump map path:< %s\n", bump_map_path);
	
	fd = open(bump_map_path, O_RDONLY);
	// printf("fd: %i\n", fd);
	str = "";
	while (str)
	{
		// printf("str: %s\n", str);
		str = get_next_line(fd);
		if (str && str[0] == '"')
		{
			str_tmp = ft_substr(str, 1, ft_strlen(str) - 5);
			free(str);
			str = str_tmp;
			// printf(">%s<\n", str);
			tab = ft_split(str, ' ');
			shades_nbr = ft_atoi(tab[2]);
			// printf("NUMBER: %i\n", shades_nbr);
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
			// printf("VALUE: \"%i\", ", char_tab[j][0]);
			if (gray_to_hex_string(&str[4], hex_output))
			{
				// data->bump_maps[j][1] = hex_to_int(hex_output);
				char_tab[j][1] = hex_to_int(hex_output);
				// printf("PAIR: \"%i\" \n", char_tab[j][1]);
			}
			else
			{
				// data->bump_maps[j][1] = hex_to_int(&str[4]);
				char_tab[j][1] = hex_to_int(&str[4]);
				// printf("PAIR: \"%i\" \n", char_tab[j][1]);
			}
		}
		free(str);
		j++;
	}
	// printf("shades_nbr: %i\n", shades_nbr);
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
						// data->bump_maps[i][l][j] = (char_tab[k][1]);
						// printf("get_texture: sphere->bump_map_nbr: %i, x: %i, y: %i\n", i, l, j);
						// printf("%i => ", int_to_grayscale(char_tab[k][1]));
						// printf("%i\n", data->bump_maps[i][l][j]);
						// printf("map %i, line: %i char %i =>", i, l, j);
						// printf("%i\n", data->bump_maps[i][l][j]);
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

/**========================================================================
 *                           FILL_STRUCT_SP
 *========================================================================**/
void	fill_struct_sp(t_data *data, double tab[])
{
	static int	i = 0;

	data->spheres[i].origin_vect.axis[0] = tab[0];
	data->spheres[i].origin_vect.axis[1] = tab[1];
	data->spheres[i].origin_vect.axis[2] = tab[2];
	data->spheres[i].origin_vect.axis[3] = 1;
	data->spheres[i].diameter = tab[3];
	data->spheres[i].radius = data->spheres[i].diameter * 0.5;
	data->spheres[i].square_radius = data->spheres[i].radius
		* data->spheres[i].radius;
	data->spheres[i].color.rgb[0] = tab[4];
	data->spheres[i].color.rgb[1] = tab[5];
	data->spheres[i].color.rgb[2] = tab[6];
	if (tab[7] == -42)
	{
		data->spheres[i].checkerboard = 1;
		data->spheres[i].bump_map_nbr = -1;
	}
	else if ((int)tab[7] != 1024)
	{
		// printf("tab[7]: %i, i: %i\n", (int)tab[7], i);
		data->spheres[i].bump_map_path = get_bmpath(data, (int)tab[7]);
		data->spheres[i].bump_map_nbr = i;
		data->spheres[i].checkerboard = 0;
		get_texture(data, i);
	}
	else
	{
		data->spheres[i].checkerboard = 0;
		data->spheres[i].bump_map_nbr = -1;
	}
	data->spheres[i].which_t = 0;
	data->spheres[i].t1 = 0.0;
	data->spheres[i].t2 = 0.0;
	i++;
}

/**========================================================================
 *                           FILL_STRUCT_CY
 *========================================================================**/
void	fill_struct_cy(t_data *data, double tab[])
{
	static int	i = 0;

	data->cylinders[i].origin_vect.axis[0] = tab[0];
	data->cylinders[i].origin_vect.axis[1] = tab[1];
	data->cylinders[i].origin_vect.axis[2] = tab[2];
	data->cylinders[i].origin_vect.axis[3] = 1;
	data->cylinders[i].axis_vect.axis[0] = tab[3];
	data->cylinders[i].axis_vect.axis[1] = tab[4];
	data->cylinders[i].axis_vect.axis[2] = tab[5];
	data->cylinders[i].diameter = tab[6];
	data->cylinders[i].radius = data->cylinders[i].diameter * 0.5;
	data->cylinders[i].square_radius = data->cylinders[i].radius
		* data->cylinders[i].radius;
	data->cylinders[i].height = tab[7];
	data->cylinders[i].color.rgb[0] = tab[8];
	data->cylinders[i].color.rgb[1] = tab[9];
	data->cylinders[i].color.rgb[2] = tab[10];
	data->cylinders[i].which_t = 0;
	data->cylinders[i].t1 = 0.0;
	data->cylinders[i].t2 = 0.0;
	i++;
}

/**========================================================================
 *                           FILL_STRUCT_PL
 *========================================================================**/
void	fill_struct_pl(t_data *data, double tab[])
{
	static int	i = 0;

	data->planes[i].origin_vect.axis[0] = tab[0];
	data->planes[i].origin_vect.axis[1] = tab[1];
	data->planes[i].origin_vect.axis[2] = tab[2];
	data->planes[i].origin_vect.axis[3] = 1;
	data->planes[i].norm_vect.axis[0] = tab[3];
	data->planes[i].norm_vect.axis[1] = tab[4];
	data->planes[i].norm_vect.axis[2] = tab[5];
	data->planes[i].color.rgb[0] = tab[6];
	data->planes[i].color.rgb[1] = tab[7];
	data->planes[i].color.rgb[2] = tab[8];
	if (tab[9] == -42)
	{
		data->planes[i].checkerboard = 1;
	}
	else if ((int)tab[9] != 1024)
	{
		data->planes[i].bump_map_path = get_bmpath(data, (int)tab[9]);
		// printf("plane bump map path: %s\n", data->planes[i].bump_map_path);
	}
	else
		data->planes[i].checkerboard = 0;
	i++;
}

/**========================================================================
 *                           FILL_STRUCT_L
 *========================================================================**/
void	fill_struct_l(t_data *data, double tab[])
{
	static int	i = 0;

	data->spotlights[i].origin_vect.axis[0] = tab[0];
	data->spotlights[i].origin_vect.axis[1] = tab[1];
	data->spotlights[i].origin_vect.axis[2] = tab[2];
	data->spotlights[i].origin_vect.axis[3] = 1;
	data->spotlights[i].intensity = tab[3];
	data->spotlights[i].color.rgb[0] = tab[4];
	data->spotlights[i].color.rgb[1] = tab[5];
	data->spotlights[i].color.rgb[2] = tab[6];
	data->spotlights[i].bulb.color = data->spotlight.color;
	data->spotlights[i].bulb.diameter = 1;
	data->spotlights[i].bulb.radius = data->spotlight.bulb.diameter * 0.5;
	data->spotlights[i].bulb.square_radius = data->spotlight.bulb.radius
		* data->spotlights[i].bulb.radius;
	data->spotlights[i].bulb.origin_vect = data->spotlight.origin_vect;
	i++;
}

void	print_triangle(t_triangle *triangle)
{
	printf("triangle: \n");
	printf("%f\n", triangle->point_a.axis[0]);
	printf("%f\n", triangle->point_a.axis[1]);
	printf("%f\n", triangle->point_a.axis[2]);
	printf("%f\n", triangle->point_b.axis[0]);
	printf("%f\n", triangle->point_b.axis[1]);
	printf("%f\n", triangle->point_b.axis[2]);
	printf("%f\n", triangle->point_c.axis[0]);
	printf("%f\n", triangle->point_c.axis[1]);
	printf("%f\n", triangle->point_c.axis[2]);
	printf("%i\n", triangle->color.rgb[0]);
	printf("%i\n", triangle->color.rgb[1] );
	printf("%i\n", triangle->color.rgb[2] );
}

void	fill_struct_tr(t_data *data, double tab[])
{
	static int	i = 0;
	data->triangles[i].point_a.axis[0] = tab[0];
	data->triangles[i].point_a.axis[1] = tab[1];
	data->triangles[i].point_a.axis[2] = tab[2];
	data->triangles[i].point_b.axis[0] = tab[3];
	data->triangles[i].point_b.axis[1] = tab[4];
	data->triangles[i].point_b.axis[2] = tab[5];
	data->triangles[i].point_c.axis[0] = tab[6];
	data->triangles[i].point_c.axis[1] = tab[7];
	data->triangles[i].point_c.axis[2] = tab[8];
	data->triangles[i].color.rgb[0] = tab[9];
	data->triangles[i].color.rgb[1] = tab[10];
	data->triangles[i].color.rgb[2] = tab[11];
	// print_triangle(&data->triangles[i]);
	i++;
}
