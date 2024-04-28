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

int	check_float(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 10)
		return (0);
	if (*str == '\0' || (*str != '-' && *str != '+' && !ft_isdigit(*str)))
		return 0;
	str++;
	while (*str != '\0' && *str != '\n')
	{
		if (*str == '.')
			i++;
		if (!ft_isdigit(*str) && *str != '.')
            return (0);
		if (*str == '-' || *str == '+')
			return (0);
		str++;
	}
	str--;
	if (!ft_isdigit(*str))
		return (0);
	if (i > 1)
		return (0);
	return (1);
}

int	check_byte(char *token)
{
	return (1);
}

int	check_data(char *str, char *token, char *check)
{
	int		len_max;
	char	**data_type;
	int i;
	
	data_type = ft_split(check, ',');

	i = 1;
	while (token)
	{
		token = ft_strtok(NULL, ", \t");
		if (data_type[i] && !ft_strcmp(data_type[i], "float") && !check_float(token))
			return (0);
		if (data_type[i] && !ft_strcmp(data_type[i], "byte") && !check_byte(token))
			return (0);
		i++;
	}
	i = 0;
	while (data_type[i])
		free(data_type[i++]);
	free(data_type);
	return (1);
}

int	is_empty_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_data_cy(char *str, char *token, char *check)
{
	return (1);
}
int	data_str_is_valid(char *str)
{
	char	*token;
	char	*data_str;
	int		status;

	status = 0;
	data_str = NULL;
	token = ft_strtok(str, ", \t");
	if (str[0] == '\n' || is_empty_str(str))
		return (1);
	if (!ft_strcmp(token, "A") && &str[1])
		status = check_data(&str[1], token, "4,float,byte,byte,byte");
	if (!ft_strcmp(token, "C") && &str[1])
		status = check_data(&str[1], token, "7,float,float,float,float,float,float,float");
	if (!ft_strcmp(token, "L") && &str[1])
		status = check_data(&str[1], token, "7,float,float,float,float,byte,byte,byte");
	if (!ft_strcmp(token, "sp") && &str[2])
		status = check_data(&str[2], token, "7,float,float,float,float,byte,byte,byte");
	if (!ft_strcmp(token, "pl") && &str[2])
		status = check_data(&str[2], token, "9,float,float,float,float,float,float,byte,byte,byte");
	if (!ft_strcmp(token, "cy") && &str[2])
		status = check_data(&str[2], token, "11,float,float,float,float,float,float,float,float,byte,byte,byte");
	ft_printf("status = %i\n", status);
	if (status == 0)
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