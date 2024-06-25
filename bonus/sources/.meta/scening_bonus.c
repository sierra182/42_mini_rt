#include <stdio.h>
#include "se_mini_struct_bonus.h"
# include <fcntl.h>
# include <unistd.h>
#include "libft.h"

void	write_fd(int fd, char *str);
void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);
void	create_filename(char *filename, int *i, char *ext);

void	pre_transform(t_data *data)
{
	int	i;
	double offset;
	double n_offset;
	double space;

	space = 15;
	i = -1;
	offset = 0;
	while (++i < data->cy_nbr *.25)
	{
		trsl_mesh(NULL, &data->cylinders[i].origin_vect, (double []){0, 0, offset});
		offset += space;
	}
	offset = 0;
	while (i < data->cy_nbr * 0.50)
	{
		offset += space;
		trsl_mesh(NULL, &data->cylinders[i].origin_vect, (double []){offset, 0, 0});
		i++;
	}
	n_offset = 0;
	while (i < data->cy_nbr * 0.75)
	{
		n_offset += space;
		trsl_mesh(NULL, &data->cylinders[i].origin_vect, (double []){offset, 0, n_offset});
		i++;
	}
	while (i < data->cy_nbr * 1)
	{
		offset -= space;
		trsl_mesh(NULL, &data->cylinders[i].origin_vect, (double []){offset,  0, n_offset});
		i++;
	}
}

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
	dprintf(fd, "%i		", (color->rgb[2]));
}

void	make_rt_file(t_data *data)
{
	int	i;
	int	fd;
	char filename[100];
	static int j = 0;

	create_filename(filename, &j, ".rt");

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);

	dprintf(fd, "A ");
	dprintf(fd, "%.*f  ", 2, data->ambiant_light.intensity);
	write_color(fd, &data->ambiant_light.color);
	write_fd(fd, "\n");

	dprintf(fd, "C ");
	write_vector(fd, &data->cam.origin_vect);
	write_vector(fd, &data->cam.forward_vect);
	dprintf(fd, "%.*f  ", 0,  data->cam.fov_deg);
	write_fd(fd, "\n");

	i = 0;
	while (i < data->sl_nbr)
	{
		dprintf(fd, "L ");
		write_vector(fd, &data->spotlights[i].origin_vect);
		dprintf(fd, "%f  ", data->spotlights[i].intensity);
		write_color(fd, &data->spotlights[i].bulb.color);
		write_fd(fd, "\n");
		i++;
	}


	i = 0;
	while (i < data->cy_nbr)
	{
		dprintf(fd, "cy ");
		write_vector(fd, &data->cylinders[i].origin_vect);
		write_vector(fd, &data->cylinders[i].axis_vect);
		dprintf(fd, "%.*f  ", 2, data->cylinders[i].diameter);
		dprintf(fd, "%.*f  ", 2, data->cylinders[i].height);
		write_color(fd, &data->cylinders[i].color);
		dprintf(fd, "%.*f", 2, (data->cylinders[i].reflexion_coef));
		write_fd(fd, "\n");
		i++;
	}
	i = 0;
	while (i < data->sp_nbr)
	{
		dprintf(fd, "sp ");
		write_vector(fd, &data->spheres[i].origin_vect);
		dprintf(fd, "%.*f  ", 2, data->spheres[i].diameter);
		write_color(fd, &data->spheres[i].color);
		dprintf(fd, "%.*f", 2, (data->spheres[i].reflexion_coef));
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
		dprintf(fd, "%.*f", 2, (data->triangles[i].reflexion_coef));
		write_fd(fd, "\n");
		i++;
	}
	i = 0;
	while (i < data->tr_nbr)
	{
		dprintf(fd, "tr ");
		write_vector(fd, &data->triangles[i].point_a);
		write_vector(fd, &data->triangles[i].point_b);
		write_vector(fd, &data->triangles[i].point_c);
		write_color(fd, &data->triangles[i].color);
		dprintf(fd, "%.*f", 2, (data->triangles[i].reflexion_coef));
		write_fd(fd, "\n");

		i++;
	}
	
	close(fd);
}
