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

int	check_data_A(char *str, char *token)
{
	int		i;
	double	j;

	j = 0;
	i = 0;
	while (token != NULL)
	{
		token = ft_strtok(NULL, ", \t");
		if (token)
		{
			if (i == 0)
			{
				j = atof(token);
				if (j < 0.0 || j > 1.0)
				{
					printf("Token %i: %s, %f\n",i , token, j);
					return (0);
				}
			}
		}
		i++;
	}
	return (1);
}

int	check_data_C(char *str, char *token)
{
	return (1);
}

int	check_data_L(char *str, char *token)
{
	return (1);
}

int	check_data_sp(char *str, char *token)
{
	return (1);
}

int	check_data_pl(char *str, char *token)
{
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

int	check_data_cy(char *str, char *token)
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
	if (!ft_strcmp(token, "A") && &str[1] && token)
		status = check_data_A(&str[1], token);
	if (!ft_strcmp(token, "C") && &str[1] && token)
		status = check_data_C(&str[1], token);
	if (!ft_strcmp(token, "L") && &str[1] && token)
		status = check_data_L(&str[1], token);
	if (!ft_strcmp(token, "sp") && &str[2] && token)
		status = check_data_sp(&str[2], token);
	if (!ft_strcmp(token, "pl") && &str[2] && token)
		status = check_data_pl(&str[2], token);
	if (!ft_strcmp(token, "cy") && &str[2] && token)
		status = check_data_cy(&str[2], token);
	ft_printf("status = %i\n", status);
	// if (status == 0)
	// 	return (0);
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