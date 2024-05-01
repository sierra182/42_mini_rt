#include "x_mini_struct.h"
#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

void	fill_struct_a(t_data *data, double tab[])
{
}

void	fill_struct_c(t_data *data, double tab[])
{
	data->cam.origin_vect.axis[0] = tab[0];
	data->cam.origin_vect.axis[1] = tab[1];
	data->cam.origin_vect.axis[2] = tab[2];
	data->cam.forward_vect.axis[0] = tab[3];
	data->cam.forward_vect.axis[1] = tab[4];
	data->cam.forward_vect.axis[2] = tab[5];
	data->cam.fov = tab[6];
}

void	fill_struct_l(t_data *data, double tab[])
{
}

void	fill_struct_sp(t_data *data, double tab[])
{
	static int	i = 0;

	data->spheres[i].origin_vect.axis[0] = tab[0];
	data->spheres[i].origin_vect.axis[1] = tab[1];
	data->spheres[i].origin_vect.axis[2] = tab[2];
	data->spheres[i].diameter = tab[3];
	data->spheres[i].square_radius = tab[3] / 2 * tab[3] / 2;
	data->spheres[i].color.rgb[0] = tab[4];
	data->spheres[i].color.rgb[1] = tab[5];
	data->spheres[i].color.rgb[2] = tab[6];
	i++;
}

void	fill_struct_cy(t_data *data, double tab[])
{
	static int	i = 0;

	i++;
}

void	fill_struct_pl(t_data *data, double tab[])
{
	static int	i = 0;

	i++;
}
