int	is_rt_file(char *map_path);
int	file_exists(char *map_path);

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include "ft_printf.h"
#include <stdio.h>
#define FILE_SIZE 1024

ssize_t read(int fd, void *buf, size_t count);

/**========================================================================
 *                           is_valid_char
 *========================================================================**/
int	is_valid_char(char c)
{
	char	*valid_char;
	int		i;

	i = 0;
	valid_char = " A	CLsplcy0123456789.,-+\n";
	while (valid_char[i])
	{
		if (c == valid_char[i])
			return (1);
		i++;
	}
	return (0);
}

/**========================================================================
 *                           element_is_present
 *========================================================================**/
int	element_is_present(char file_content[], char *el)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while(file_content[i])
	{
		if (!ft_strncmp(&file_content[i], el, ft_strlen(el)) && (!file_content[i + ft_strlen(el)] || ft_isspace(file_content[i + ft_strlen(el)])) && (!file_content[i - 1] || ft_isspace(file_content[i - 1])))
		{
			// printf("char: >%c<\n", file_content[i - 1]);
			n++;
		}
		i++;
	}
	return (n);
}
/**========================================================================
 *                           all_necessary_elements_are_present
 *========================================================================**/
int	all_necessary_elements_are_present(char file_content[])
{
	if (element_is_present(file_content, "A") != 1)
		return (0);
	if (element_is_present(file_content, "C") != 1)
		return (0);
	if (element_is_present(file_content, "L") != 1)
		return (0);
	if (!element_is_present(file_content, "sp"))
		return (0);
	if (!element_is_present(file_content, "cy"))
		return (0);
	if (!element_is_present(file_content, "pl"))
		return (0);	
	return (1);
}

/**========================================================================
 *                           is_only_valid_chars
 *========================================================================**/
int	is_only_valid_chars(char file_content[])
{
	int	i;
	
	i = 0;
	while (file_content[i])
	{
		if (!is_valid_char(file_content[i]))
			return (0);
		i++;
	}
	return (1);
}

/**========================================================================
 *                           check_float
 *========================================================================**/
int	check_float(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	if (ft_strlen(str) > 10)
		return (0);
	if (*str == '\0' || (*str != '-' && *str != '+' && !ft_isdigit(*str)))
		return 0;
	str++;
	while (*str != '\0' && *str != '\n')
	{
		if (*str == '.')
			i++;
		if ((!ft_isdigit(*str) && *str != '.') || *str == '-' || *str == '+')
            return (0);
		str++;
	}
	str--;
	if (!ft_isdigit(*str) || i > 1)
		return (0);
	return (1);
}

/**========================================================================
 *                           check_byte
 *========================================================================**/
int	check_byte(char *str)
{
	int	num;

	if (str == NULL)
		return (1);
	num = ft_atoi(str);
	if (ft_strlen(str) > 3)
		return (0);	
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
		return 0;
		str++;
	}
	if (num < 0 || num > 255)
		return (0);
	str--;
	return (1);
}

/**========================================================================
 *                           is_empty_str
 *========================================================================**/
int	is_empty_str(char *str)
{
	int	i;

	i = 0;
	if(str[i] == '\n')
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
 *                           check_data
 *? added 	if (i > len_max + 2) return (0); to check arument nbr
 *========================================================================**/
int	check_data(char *token, char *check)
{
	int		len_max;
	char	**data_type;
	int i;
	
	data_type = ft_split(check, ',');
	len_max = ft_atoi(data_type[0]);
	i = 1;
	while (token)
	{
		token = ft_strtok(NULL, ", \t\n");
		if (data_type[i - 1] == NULL)
			return (0);
		if (data_type[i] && !ft_strcmp(data_type[i], "fl") && !check_float(token))
			return (0);
		if (data_type[i] && !ft_strcmp(data_type[i], "bt") && !check_byte(token))
			return (0);
		i++;
	}
	if (i != len_max + 2)
		return (0);
	i = 0;
	while (data_type[i])
		free(data_type[i++]);
	free(data_type);
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
	else
		return (0);
	if (check_data(token, data_str) == 0)
		return (0);
	return (1);
}

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
			break;
		if (is_empty_str(str))
			continue ;
		if (!data_str_is_valid(str))
			return (free(str), 0);
		free(str);
	}
	return (1);
}

/**========================================================================
 *                           file_content_is_correct
 *========================================================================**/
int	file_content_is_correct(char *map_path)
{
	int		map_fd;
	int		file_size;
	char	*str;
	char	file_content[1024];

	map_fd = open(map_path, O_RDONLY);
	ft_bzero(file_content, FILE_SIZE);
	file_size = read(map_fd, file_content, FILE_SIZE);
	if (file_size > 1024)
		return (0);
	if (!is_only_valid_chars(file_content))
		return (0);
	if (!all_necessary_elements_are_present(file_content))
		return (0);
	close(map_fd);
	if (!elements_data_are_valid(map_path))
		return (0);
	return (1);
}

/**========================================================================
 *                           parse
 *========================================================================**/
int	parse(char *map_path)
{
	if (!is_rt_file(map_path))
		return (0);
	if (!file_exists(map_path))
		return (0);
	if (!file_content_is_correct(map_path))
		return (0);
	return (1);
}