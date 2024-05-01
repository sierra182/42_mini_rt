#include "x_mini_struct.h"
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	element_is_present(char file_content[], char *el);


int	create_data_structs(t_data *data, char *map_path)
{
	int		file_size;
	int		map_fd;
	int		nbr;
	char	file_content[1024];

	ft_bzero(file_content, 1024);

	map_fd = open(map_path, O_RDONLY);
	file_size = read(map_fd, file_content, 1024);
	close(map_fd);

	// printf("file_content: %s", file_content);

	data->sp_nbr = element_is_present(file_content, "sp");
	printf("sp nbr: %i\n", data->sp_nbr);
	data->spheres = (t_sphere *)malloc(sizeof(t_sphere) * data->sp_nbr);
	if (data->spheres == NULL)
		return (0);

	data->cy_nbr = element_is_present(file_content, "cy");
	printf("cy nbr: %i\n", data->cy_nbr);
	data->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder) * data->cy_nbr);
	if (data->cylinders == NULL)
		return (0);

	data->pl_nbr = element_is_present(file_content, "pl");
	printf("pl nbr: %i\n", data->pl_nbr);
	data->planes = (t_plane *)malloc(sizeof(t_plane) * data->pl_nbr);
	if (data->planes == NULL)
		return (0);
		
	return (1);
}