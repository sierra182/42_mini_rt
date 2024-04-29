#include "elements_data_are_valid.h"

/**========================================================================
 *                           elements_data_are_valid
 *========================================================================**/
int	elements_data_are_valid(char *map_path)
{
	int		map_fd;
	char	*str;

	map_fd = open(map_path, O_RDONLY);
	while (1)
	{
		str = get_next_line(map_fd);
		if (!str)
			break ;
		if (is_empty_str(str))
			continue ;
		if (!data_str_is_valid(str))
			return (free(str), 0);
		free(str);
	}
	return (1);
}

/**========================================================================
 *                           is_empty_str
 *========================================================================**/
int	is_empty_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\n')
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**========================================================================
 *                           data_str_is_valid
 *========================================================================**/
int	data_str_is_valid(char *str)
{
	char	*token;
	int		status;
	char	*data_str;

	status = 0;
	token = ft_strtok(str, ", \t");
	if (!ft_strcmp(token, "A"))
		data_str = "4,fl,bt,bt,bt";
	else if (!ft_strcmp(token, "C"))
		data_str = "7,fl,fl,fl,fl,fl,fl,fl";
	else if (!ft_strcmp(token, "L"))
		data_str = "7,fl,fl,fl,fl,bt,bt,bt";
	else if (!ft_strcmp(token, "sp"))
		data_str = "7,fl,fl,fl,fl,bt,bt,bt";
	else if (!ft_strcmp(token, "pl"))
		data_str = "9,fl,fl,fl,fl,fl,fl,bt,bt,bt";
	else if (!ft_strcmp(token, "cy"))
		data_str = "11,fl,fl,fl,fl,fl,fl,fl,fl,bt,bt,bt";
	else if (!ft_strncmp(token, "#", 1))
		return (1);
	else
		return (0);
	if (check_data(token, data_str) == 0)
		return (0);
	return (1);
}

/**========================================================================
 *                           check_data
 *? added 	if (i > len_max + 2) return (0); to check arument nbr
 *========================================================================**/
int	check_data(char *token, char *check)
{
	int		len_max;
	char	**data_type;
	int		i;

	data_type = ft_split(check, ',');
	len_max = ft_atoi(data_type[0]);
	i = 1;
	while (token)
	{
		token = ft_strtok(NULL, ", \t\n");
		if (data_type[i - 1] == NULL)
			return (0);
		if (data_type[i] && !ft_strcmp(data_type[i], "fl")
			&& !check_float(token))
			return (0);
		if (data_type[i] && !ft_strcmp(data_type[i], "bt")
			&& !check_byte(token))
			return (0);
		i++;
	}
	if (i != len_max + 2)
		return (0);
	free_tab(data_type);
	return (1);
}

void	free_tab(char **data_type)
{
	int	i;

	i = 0;
	while (data_type[i])
		free(data_type[i++]);
	free(data_type);
}
