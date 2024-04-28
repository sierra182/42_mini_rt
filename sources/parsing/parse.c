int	is_rt_file(char *map_path);
int	file_exists(char *map_path);

#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	file_content_is_correct(char *map_path)
{
	int		map_fd;

	map_fd = open(map_path, O_RDONLY);


	close(map_fd);
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