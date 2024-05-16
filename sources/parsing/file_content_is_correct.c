#include "file_content_is_correct.h"
#include "get_next_line.h"

/**========================================================================
 *                           file_content_is_correct
 *========================================================================**/
int	file_content_is_correct(t_data *data, char *map_path)
{
	int		map_fd;
	int		file_size;
	char	*str;
	char	file_content[FILE_SIZE];

	map_fd = open(map_path, O_RDONLY);
	ft_bzero(file_content, FILE_SIZE);
	file_size = read(map_fd, file_content, FILE_SIZE);
	if (file_size > FILE_SIZE)
	{
		printf("file_content_is_correct 0\n");
		return (0);
	}

	while (1)
	{
		str = get_next_line(map_fd);
		if (!str)
			break ;
		if (!is_only_valid_chars(str))
		{
			printf("file_content_is_correct 1\n");
			return (0);
		}
		
		free(str);
	}

	if (!all_necessary_elements_are_present(data, map_path))
		{
			printf("file_content_is_correct 2\n");
			return (0);
		}


	if (!elements_data_are_valid(map_path))
	{
		printf("file_content_is_correct 3\n");
		return (0);
	}
	close(map_fd);
	return (1);
}

/**========================================================================
 *                           is_only_valid_chars
 *========================================================================**/
int	is_only_valid_chars(char str[])
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
			return (1);
		if (!is_valid_char(str[i]))
		{
			printf("is_only_valid_chars\n");
			return (0);
		}
		i++;
	}
	return (1);
}

/**========================================================================
 *                           is_valid_char
 *========================================================================**/
int	is_valid_char(char c)
{
	char	*valid_char;
	int		i;

	valid_char = " #A	CLsplcy0123456789.,-+\n";
	i = 0;
	while (valid_char[i])
	{
		if (c == valid_char[i])
			return (1);
		i++;
	}
	printf("is_valid_char\n");
	return (0);
}
