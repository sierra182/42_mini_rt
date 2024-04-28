int	is_rt_file(char *map_path);
int	file_exists(char *map_path);

/**========================================================================
 *                           parse
 *========================================================================**/
int	parse(char *map_path)
{
	if (!is_rt_file(map_path) || !file_exists(map_path))
		return (0);
	return (1);
}