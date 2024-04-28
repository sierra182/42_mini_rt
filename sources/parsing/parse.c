#include "ft_printf.h"
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>

/**========================================================================
 *                           display_error
 *========================================================================**/
void	display_error(void)
{
	if (write(2, "Error\n", 6) < 0)
		perror("display_error\n");
}

/**========================================================================
 *                           is_rt_file
 *========================================================================**/
int	is_rt_file(char *map_path)
{
	while (*map_path)
	{
		if (ft_strncmp(map_path, ".rt", 4) == 0)
			return (1);
		map_path++;
	}
	return (0);
}

/**========================================================================
 *                           file_exists
 *========================================================================**/
int	file_exists(char *map_path)
{
	int		map_fd;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (0);
	return (1);
}


/**========================================================================
 *                           parse
 *========================================================================**/
int	parse(char *map_path)
{
	if (!is_rt_file(map_path) || !file_exists(map_path))
		return (0);
	return (1);
}