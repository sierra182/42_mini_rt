/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_data_are_valid_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:44:57 by svidot            #+#    #+#             */
/*   Updated: 2024/06/28 10:38:06 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements_data_are_valid_bonus.h"

/**========================================================================
 *                           ELEMENTS_DATA_ARE_VALID
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
			close(map_fd);
			return (0);
		}
		free(str);
	}
	close(map_fd);
	return (1);
}

/**========================================================================
 *                           DATA_STR_IS_VALID
 *========================================================================**/
int	data_str_is_valid(char *str)
{
	char	*token;
	char	*data_str;

	token = ft_strtok(str, ", \t");
	if (!ft_strcmp(token, "A"))
		data_str = "5,ltr,byt,byt,byt";
	else if (!ft_strcmp(token, "C"))
		data_str = "8,fl,fl,fl,vecr,vecr,vecr,fov";
	else if (!ft_strcmp(token, "L"))
		data_str = "8,fl,fl,fl,ltr,byt,byt,byt";
	else if (!ft_strcmp(token, "sp"))
		data_str = "10,fl,fl,fl,ufl,byt,byt,byt,ltr,check";
	else if (!ft_strcmp(token, "pl"))
		data_str = "11,fl,fl,fl,vecr,vecr,vecr,byt,byt,byt,ltr";
	else if (!ft_strcmp(token, "cy"))
		data_str = "13,fl,fl,fl,vecr,vecr,vecr,ufl,ufl,byt,byt,byt,ltr";
	else if (!ft_strcmp(token, "tr"))
		data_str = "14,fl,fl,fl,fl,fl,fl,fl,fl,fl,byt,byt,byt,ltr";
	else if (!ft_strncmp(token, "#", 1))
		return (1);
	else
		return (0);
	if (check_data(token, data_str) == 0)
		return (0);
	return (1);
}

/**========================================================================
 *                           CHECK_DATA
 *========================================================================**/
int	check_data(char *token, char *check)
{
	int		len_max;
	char	**num;
	int		i;

	num = ft_split(check, ',');
	len_max = ft_atoi(num[0]);
	i = 1;
	if (check_data_nbrs(token, num, &i) == 0)
		return (free_tab(num), 0);
	if (len_max != 10 && i != len_max + 1)
		return (free_tab(num), 0);
	if (len_max == 10 && i != len_max + 1 && i != len_max)
		return (free_tab(num), 0);
	free_tab(num);
	return (1);
}

/**========================================================================
 *                           IS_VALID_XPM
 *========================================================================**/
int	is_valid_xpm(char *str)
{
	if (!str || ft_strlen(str) < 5 || !file_exists(str))
		return (0);
	if (!ft_strcmp(&str[ft_strlen(str) - 4], ".xpm") && file_exists(str))
	{
		return (1);
	}
	return (0);
}

/**========================================================================
 *                           CHECK_DATA_NBRS
 *========================================================================**/
int	check_data_nbrs(char *token, char	**num, int *i)
{
	while (token)
	{
		token = ft_strtok(NULL, ", \t\n");
		if (num[*i - 1] == NULL)
			return (0);
		if (num[*i] && !ft_strcmp(num[*i], "ltr") && !chck_fl(token, LTR))
			return (0);
		if (num[*i] && !ft_strcmp(num[*i], "vecr") && !chck_fl(token, VECR))
			return (0);
		if (num[*i] && !ft_strcmp(num[*i], "byt") && !chck_bt(token, BYT))
			return (0);
		if (num[*i] && !ft_strcmp(num[*i], "fov") && !chck_bt(token, FOV))
			return (0);
		if (num[*i] && !ft_strcmp(num[*i], "fl") && !chck_fl(token, FL))
			return (0);
		if (num[*i] && !ft_strcmp(num[*i], "ufl") && !chck_fl(token, UFL))
			return (0);
		if (num[*i] && !ft_strcmp(num[*i], "check") && token
			&& (ft_strcmp(token, "checkerboard") && !is_valid_xpm(token)))
			return (0);
		(*i)++;
	}
	return (1);
}
