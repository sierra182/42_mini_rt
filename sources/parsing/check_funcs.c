#include "check_file.h"
#include <stdlib.h>
#include "get_next_line.h"
#include <unistd.h>
#include "libft.h"
#include <fcntl.h>

#define FILE_SIZE 1024

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
		return (0);
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
			return (0);
		str++;
	}
	if (num < 0 || num > 255)
		return (0);
	str--;
	return (1);
}
