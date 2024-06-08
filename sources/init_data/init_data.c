#include "init_data.h"

# include "se_mini_struct.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>

void	fill_struct_a(t_data *data, double tab[]);
void	fill_struct_c(t_data *data, double tab[]);
void	fill_struct_l(t_data *data, double tab[]);
void	fill_struct_cy(t_data *data, double tab[]);
void	fill_struct_pl(t_data *data, double tab[]);
void	fill_struct_sp(t_data *data, double tab[]);
int		create_data_structs(t_data *data, char *map_path);
double	*fill_tab(char *str, double tab[]);
double	*get_element_data(char *map_path, double tab[], char *el);
int		element_is_present(char *map_path, char *el);
void	get_elements_number(t_data *data, char *map_path);
int		update_cam(t_cam *cam);
void	post_init_cam(t_cam *cam);
void	init_vars(t_data *data);

/**========================================================================
 *                             COMMENT BLOCK
 * tab cells are initialized at 1024.
 * => values of floats for coordinates should not be greater than 1024 
 *========================================================================**/

/**========================================================================
 *                           save_data
 * for reset option
 *========================================================================**/
void	save_data(t_data *data)
{
	data->data_cpy = (t_data *) ft_calloc(1, sizeof(t_data));
	*data->data_cpy = *data;
	data->data_cpy->spheres = (t_sphere *) ft_calloc(data->sp_nbr,
			sizeof(t_sphere));
	ft_memcpy(data->data_cpy->spheres, data->spheres, data->sp_nbr
		* sizeof(t_sphere));
	data->data_cpy->cylinders = (t_cylinder *) ft_calloc(data->cy_nbr,
			sizeof(t_cylinder));
	ft_memcpy(data->data_cpy->cylinders, data->cylinders, data->cy_nbr
		* sizeof(t_cylinder));
	data->data_cpy->planes = (t_plane *) ft_calloc(data->pl_nbr,
			sizeof(t_plane));
	ft_memcpy(data->data_cpy->planes, data->planes, data->pl_nbr
		* sizeof(t_plane));
	add_exit_struct(data->data_cpy, DATA);
}

/**========================================================================
 *                           init_data
 *========================================================================**/
int	init_data(char *map_path, t_data *data)
{
	double	tab[20];

	get_elements_number(data, map_path);
	if (create_data_structs(data, map_path) == 0)
		return (0);
	while (get_element_data(map_path, tab, "A") != NULL)
		fill_struct_a(data, tab);
	while (get_element_data(map_path, tab, "C") != NULL)
		fill_struct_c(data, tab);
	while (get_element_data(map_path, tab, "L") != NULL)
		fill_struct_l(data, tab);
	while (get_element_data(map_path, tab, "sp") != NULL)
		fill_struct_sp(data, tab);
	while (get_element_data(map_path, tab, "cy") != NULL)
		fill_struct_cy(data, tab);
	while (get_element_data(map_path, tab, "pl") != NULL)
		fill_struct_pl(data, tab);
	init_vars(data);
	return (1);
}

/**========================================================================
 *                           INIT_VARS
 *========================================================================**/
void	init_vars(t_data *data)
{
	data->refresh = 1;
	data->event.ctrl_ispressed = 0;
	data->event.legend = 0;
	data->event.actual_mode = 0;
	data->event.actual_mesh.ref = NULL;
	post_init_cam(&data->cam);
	update_cam(&data->cam);
	save_data(data);
}

/**========================================================================
 *                           get_elements_number
 *========================================================================**/
void	get_elements_number(t_data *data, char *map_path)
{
	int	val;

	val = 1;
	data->sp_nbr = element_is_present(map_path, "sp");
	if (data->sp_nbr == 0)
		val = 0;
	data->cy_nbr = element_is_present(map_path, "cy");
	if (data->cy_nbr == 0)
		val = 0;
	data->pl_nbr = element_is_present(map_path, "pl");
	if (data->pl_nbr == 0)
		val = 0;
}

/**========================================================================
 *                           get_element_data
 *========================================================================**/
double	*get_element_data(char *map_path, double tab[], char *el)
{
	static int	map_fd = -1;
	char		*str;
	int			i;

	if (map_fd == -1)
		map_fd = open(map_path, O_RDONLY);
	while (1)
	{
		str = get_next_line(map_fd);
		if (str == NULL)
			break ;
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		if (ft_strnstr(&str[i], el, ft_strlen(el)))
		{
			tab = fill_tab(str, tab);
			free (str);
			return (tab);
		}
		free(str);
	}
	close(map_fd);
	map_fd = -1;
	return (NULL);
}
