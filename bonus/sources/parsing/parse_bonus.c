#include "parse_bonus.h"

/**========================================================================
 *                           PARSE
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

/**========================================================================
 *                           IS_RT_FILE
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
 *                           FILE_EXISTS
 *========================================================================**/
int	file_exists(char *map_path)
{
	int		map_fd;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (0);
	close(map_fd);
	return (1);
}