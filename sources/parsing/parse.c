int	is_rt_file(char *map_path);
int	file_exists(char *map_path);

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include "ft_printf.h"
#define FILE_SIZE 1024

ssize_t read(int fd, void *buf, size_t count);

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
			// ft_printf("char: >%c<\n", file_content[i - 1]);
			n++;
		}
		i++;
	}
	return (n);
}
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

int	file_content_is_correct(char *map_path)
{
	int		map_fd;
	int		file_size;
	char	*str;
	char	file_content[1024];
	int	i;


	map_fd = open(map_path, O_RDONLY);
	ft_bzero(file_content, FILE_SIZE);
	file_size = read(map_fd, file_content, FILE_SIZE);

	if (!is_only_valid_chars(file_content))
		return (0);
	if (!all_necessary_elements_are_present(file_content))
		return (0);
	while (1)
	{
		str = get_next_line(map_fd);
		
		if (str == NULL)
			break ;
		free (str);
	}
	close(map_fd);
	return (1);
}

#include <string.h>

void	get_tokens(void)
{
	char str[] = "	50.0,0.0,20.6		0.0,0.0,1.0			14.2		21.42		10,0,255";
    char *token;

    // Diviser la chaîne en tokens basés sur l'espace et la tabulation
    token = ft_strtok(str, ", \t");
    while (token != NULL) {
        ft_printf("Token: %s\n", token);
        token = ft_strtok(NULL, ", \t"); // NULL indique de continuer à partir de la dernière position
    }
    // return 0;
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
	get_tokens();
	return (1);
}