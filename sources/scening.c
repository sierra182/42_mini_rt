#include <stdio.h>
#include "x_mini_struct.h"
# include <fcntl.h>
# include <unistd.h>
void write_fd(int fd, char *str);
#include "libft.h"

/* 

typedef struct s_data
{
	int				refresh;
	int				sp_nbr;
	int				pl_nbr;
	int				cy_nbr;
	t_event			event;
	t_cam			cam;
	t_sphere		*spheres;
	t_cylinder		*cylinders;
	t_plane			*planes;
	t_spotlight		spotlight;
	t_ambiant_light	ambiant_light;
	struct s_data	*data_cpy;
}	t_data;

 */


// void	fill_struct_sp(t_data *data, double tab[])
// {
// 	static int	i = 0;

// 	data->spheres[i].origin_vect.axis[0] = tab[0];
// 	data->spheres[i].origin_vect.axis[1] = tab[1];
// 	data->spheres[i].origin_vect.axis[2] = tab[2];
// 	data->spheres[i].origin_vect.axis[3] = 1;
// 	data->spheres[i].diameter = tab[3];
// 	data->spheres[i].square_radius = tab[3] / 2 * tab[3] / 2;
// 	data->spheres[i].color.rgb[0] = tab[4];
// 	data->spheres[i].color.rgb[1] = tab[5];
// 	data->spheres[i].color.rgb[2] = tab[6];
// 	i++;
// }

// void	fill_struct_cy(t_data *data, double tab[])
// {
// 	static int	i = 0;


// 	data->cylinders[i].diameter = tab[6];
// 	data->cylinders[i].radius = tab[6] / 2;
// 	data->cylinders[i].square_radius = (tab[6] / 2) * (tab[6] / 2);
// 	data->cylinders[i].height = tab[7];
// 	data->cylinders[i].color.rgb[0] = tab[8];
// 	data->cylinders[i].color.rgb[1] = tab[9];
// 	data->cylinders[i].color.rgb[2] = tab[10];
// 	i++;
// }

// void	fill_struct_pl(t_data *data, double tab[])
// {
// 	static int	i = 0;

// 	data->planes[i].origin_vect.axis[0] = tab[0];
// 	data->planes[i].origin_vect.axis[1] = tab[1];
// 	data->planes[i].origin_vect.axis[2] = tab[2];
// 	data->planes[i].origin_vect.axis[3] = 1;
// 	data->planes[i].norm_vect.axis[0] = tab[3];
// 	data->planes[i].norm_vect.axis[1] = tab[4];
// 	data->planes[i].norm_vect.axis[2] = tab[5];
// 	data->planes[i].color.rgb[0] = tab[6];
// 	data->planes[i].color.rgb[1] = tab[7];
// 	data->planes[i].color.rgb[2] = tab[8];
// 	i++;
// }


// void	print_sphere(t_sphere sphere)
// {
// 	printf("sphere.origin_vect.axis[0]: %f\n", sphere.origin_vect.axis[0]);
// 	printf("sphere.origin_vect.axis[1]: %f\n", sphere.origin_vect.axis[1]);
// 	printf("sphere.origin_vect.axis[2]: %f\n", sphere.origin_vect.axis[2]);
// 	printf("sphere.diameter: %f\n", sphere.diameter);
// 	printf("spheres.square_radius: %f\n", sphere.square_radius);
// 	printf("spheres.color.rgb[0]: %i\n", sphere.color.rgb[0]);
// 	printf("spheres.color.rgb[1]: %i\n", sphere.color.rgb[1]);
// 	printf("spheres.color.rgb[2]: %i\n", sphere.color.rgb[2]);
// }

void	write_vector(int fd, void *vector)
{
	t_ray_vector *vec = (t_ray_vector *)vector;

	
	dprintf(fd, "%f, ", (vec->axis[0]));
	
	dprintf(fd, "%f, ", (vec->axis[1]));
	dprintf(fd, "%f, ", (vec->axis[0]));
	write_fd(fd, "  ");
}

void	write_color(int fd, t_color *color)
{
	dprintf(fd, "%i, ", (color->rgb[0]));
	dprintf(fd, "%i, ", (color->rgb[1]));
	dprintf(fd, "%i, ", (color->rgb[0]));
	write_fd(fd, "  ");
}


void	make_rt_file(t_data *data)
{
	int	i;
	int	fd;

	fd = open("new_scene.rt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

	i = 0;
	while (i < data->cy_nbr)
	{
		dprintf(fd, "cy ");
		write_vector(fd, &data->cylinders[i].origin_vect);
		write_vector(fd, &data->cylinders[i].axis_vect);
		dprintf(fd, "%f  ", data->cylinders[i].diameter);
		dprintf(fd, "%f  ", data->cylinders[i].height);
		write_color(fd, &data->cylinders[i].color);
		write_fd(fd, "\n");
		i++;
	}
	i = 0;
	while (i < data->sp_nbr)
	{
		dprintf(fd, "sp ");
		write_vector(fd, &data->spheres[i].origin_vect);
		dprintf(fd, "%f  ", data->spheres[i].diameter);
		write_color(fd, &data->spheres[i].color);
		write_fd(fd, "\n");
		i++;
	}
	i = 0;
	while (i < data->pl_nbr)
	{
		dprintf(fd, "pl ");
		write_vector(fd, &data->planes[i].origin_vect);
		write_vector(fd, &data->planes[i].norm_vect);
		write_color(fd, &data->planes[i].color);
		write_fd(fd, "\n");
		i++;
	}
	

	close(fd);
}