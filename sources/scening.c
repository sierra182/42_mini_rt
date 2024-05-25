#include <stdio.h>
#include "x_mini_struct.h"
# include <fcntl.h>
# include <unistd.h>
void write_fd(int fd, char *str);
#include "libft.h"

void	write_vector(int fd, void *vector)
{
	t_ray_vector *vec = (t_ray_vector *)vector;

	
	dprintf(fd, "%.*f,", 2, (vec->axis[0]));
	
	dprintf(fd, "%.*f,", 2, (vec->axis[1]));
	dprintf(fd, "%.*f", 2, (vec->axis[2]));
	write_fd(fd, "  ");
}

void	write_color(int fd, t_color *color)
{
	dprintf(fd, "%i,", (color->rgb[0]));
	dprintf(fd, "%i,", (color->rgb[1]));
	dprintf(fd, "%i", (color->rgb[2]));
	write_fd(fd, "\n");

}

void	make_rt_file(t_data *data)
{
	int	i;
	int	fd;

	fd = open("new_scene.rt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

	dprintf(fd, "A ");
	dprintf(fd, "%.*f  ", 2, data->ambiant_light.intensity);
	write_color(fd, &data->ambiant_light.color);

	dprintf(fd, "C ");
	write_vector(fd, &data->cam.origin_vect);
	write_vector(fd, &data->cam.forward_vect);
	dprintf(fd, "%.*f  ", 0,  data->cam.fov_deg);
	write_fd(fd, "\n");

	dprintf(fd, "L ");
	write_vector(fd, &data->spotlight.origin_vect);
	dprintf(fd, "%f  ", data->spotlight.intensity);
	write_color(fd, &data->spotlight.bulb.color);

	i = 0;
	while (i < data->cy_nbr)
	{
		dprintf(fd, "cy ");
		write_vector(fd, &data->cylinders[i].origin_vect);
		write_vector(fd, &data->cylinders[i].axis_vect);
		dprintf(fd, "%.*f  ", 2, data->cylinders[i].diameter);
		dprintf(fd, "%.*f  ", 2, data->cylinders[i].height);
		write_color(fd, &data->cylinders[i].color);
		i++;
	}
	i = 0;
	while (i < data->sp_nbr)
	{
		dprintf(fd, "sp ");
		write_vector(fd, &data->spheres[i].origin_vect);
		dprintf(fd, "%.*f  ", 2, data->spheres[i].diameter);
		write_color(fd, &data->spheres[i].color);
		i++;
	}
	i = 0;
	while (i < data->pl_nbr)
	{
		dprintf(fd, "pl ");
		write_vector(fd, &data->planes[i].origin_vect);
		write_vector(fd, &data->planes[i].norm_vect);
		write_color(fd, &data->planes[i].color);
		i++;
	}
	
	close(fd);
}
