#include "elements_data_are_valid.h"


#include "ft_printf.h" 

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
		{
			free(str);
			continue ;
		}
		if (!data_str_is_valid(str))
		{
			free(str);
			get_next_line(42);
			return (0);
		}
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
 * ltr[0.0,1.0]
 * vecr[-1.0,1.0]
 * bt: [0,255]
 * fov: [0,180]
 * fl: float (limit: strlen=10)
 *========================================================================**/
int	data_str_is_valid(char *str)
{
	char	*token;
	int		status;
	char	*data_str;

	status = 0;
	token = ft_strtok(str, ", \t");
	if (!ft_strcmp(token, "A"))
		data_str = "4,ltr,byt,byt,byt";
	else if (!ft_strcmp(token, "C"))
		data_str = "7,fl,fl,fl,vecr,vecr,vecr,fov";
	else if (!ft_strcmp(token, "L"))
		data_str = "7,fl,fl,fl,ltr,byt,byt,byt";
	else if (!ft_strcmp(token, "sp"))
		data_str = "7,fl,fl,fl,fl,byt,byt,byt";
	else if (!ft_strcmp(token, "pl"))
		data_str = "9,fl,fl,fl,vecr,vecr,vecr,byt,byt,byt";
	else if (!ft_strcmp(token, "cy"))
		data_str = "11,fl,fl,fl,vecr,vecr,vecr,fl,fl,byt,byt,byt";
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
 * 
 * fl: float (limit: strlen=10)
 * ltr[0.0,1.0]
 * vecr[-1.0,1.0]
 * bt: [0,255]
 * fov: [0,180]
 * chck_fl(char *str)
 * chck_bt(char *str)
 *========================================================================**/
int	check_data(char *token, char *check)
{
	int		len_max;
	char	**num;
	int		i;

	num = ft_split(check, ',');
	len_max = ft_atoi(num[0]);
	i = 1;
	while (token)
	{
		token = ft_strtok(NULL, ", \t\n");
		if (num[i - 1] == NULL)
			return (free_tab(num), 0);
		if (num[i] && !ft_strcmp(num[i], "ltr") && !chck_fl(token, LTR))
			return (free_tab(num), 0);
		if (num[i] && !ft_strcmp(num[i], "vecr") && !chck_fl(token, VECR))
			return (free_tab(num), 0);
		if (num[i] && !ft_strcmp(num[i], "byt") && !chck_bt(token, BYT))
			return (free_tab(num), 0);
		if (num[i] && !ft_strcmp(num[i], "fov") && !chck_bt(token, FOV))
			return (free_tab(num), 0);
		if (num[i] && !ft_strcmp(num[i], "fl") && !chck_fl(token, FL))
			return (free_tab(num), 0);
		i++;
	}
	if (i != len_max + 2)
		return (free_tab(num), 0);
	free_tab(num);
	return (1);
}

/**========================================================================
 *                           free_tab
 *========================================================================**/
void	free_tab(char **num)
{
	int	i;

	i = 0;
	while (num[i])
		free(num[i++]);
	free(num);
}