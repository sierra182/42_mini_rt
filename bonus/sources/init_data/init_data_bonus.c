#include "init_data_bonus.h"

/**========================================================================
 *                             INIT_DATA
 * tab cells are initialized at 1024.
 * => values of floats for coordinates should not be greater than 1024 
 *========================================================================**/

/**========================================================================
 *                           SAVE_DATA
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
	data->data_cpy->spotlights = (t_spotlight *) ft_calloc(data->sl_nbr,
			sizeof(t_spotlight));
	ft_memcpy(data->data_cpy->spotlights, data->spotlights, data->sl_nbr
		* sizeof(t_spotlight));
	add_exit_struct(data->data_cpy, DATA);
}

/**========================================================================
 *                           INIT_DATA
 *========================================================================**/
int	init_data(char *map_path, t_data *data)
{
	double	tab[20];
	int		i;

	get_elements_number(data, map_path);
	if (create_data_structs(data) == 0)
		return (0);
	i = 0;
	while (i < 100)
		data->bump_map_paths[i++] = NULL;
	while (get_element_data(NULL, map_path, tab, "A") != NULL)
		fill_struct_a(data, tab);
	while (get_element_data(NULL, map_path, tab, "C") != NULL)
		fill_struct_c(data, tab);
	while (get_element_data(NULL, map_path, tab, "L") != NULL)
		fill_struct_l(data, tab);
	while (get_element_data(data, map_path, tab, "sp") != NULL)
		fill_struct_sp(data, tab);
	while (get_element_data(data, map_path, tab, "cy") != NULL)
		fill_struct_cy(data, tab);
	while (get_element_data(data, map_path, tab, "pl") != NULL)
		fill_struct_pl(data, tab);
	while (get_element_data(data, map_path, tab, "tr") != NULL)
		fill_struct_tr(data, tab);
	init_vars(data);
	return (1);
}

/**========================================================================
 *                           INIT_VARS
 *========================================================================**/
void	init_vars(t_data *data)
{
	data->is_test = 0;
	data->refresh = 1;
	data->event.ctrl_ispressed = 0;
	data->event.legend = 0;
	data->event.actual_mode = 0;
	data->event.actual_mesh.ref = NULL;
	data->event.actual_light = NULL;
	post_init_cam(&data->cam);
	update_cam(&data->cam);
	save_data(data);
	data->bump_map_paths[0] = NULL;
}

/**========================================================================
 *                           GET_ELEMENTS_NUMBER
 *========================================================================**/
void	get_elements_number(t_data *data, char *map_path)
{
	data->sp_nbr = element_is_present(map_path, "sp");
	data->cy_nbr = element_is_present(map_path, "cy");
	data->pl_nbr = element_is_present(map_path, "pl");
	data->sl_nbr = element_is_present(map_path, "L");
	data->tr_nbr = element_is_present(map_path, "tr");
}

/**========================================================================
 *                           GET_ELEMENT_DATA
 *========================================================================**/
double	*get_element_data(t_data *data, char *map_path, double tab[], char *el)
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
			tab = fill_tab(data, str, tab);
			free (str);
			return (tab);
		}
		free(str);
	}
	close(map_fd);
	map_fd = -1;
	return (NULL);
}
