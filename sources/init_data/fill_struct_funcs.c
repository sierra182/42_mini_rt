#include "fill_struct_funcs.h"

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
	data->cam.fov_deg = tab[6];
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

void	print_plane(t_plane *plane, int i)
{
	printf("plane %i: \n", i);
	printf("data->plane.origin_vect.axis[0]: %f\n", plane->origin_vect.axis[0]);
	printf("data->plane.origin_vect.axis[1]: %f\n", plane->origin_vect.axis[1]);
	printf("data->plane.origin_vect.axis[2]: %f\n", plane->origin_vect.axis[2]);
	printf("data->plane.origin_vect.axis[0]: %f\n", plane->norm_vect.axis[0]);
	printf("data->plane.origin_vect.axis[1]: %f\n", plane->norm_vect.axis[1]);
	printf("data->plane.origin_vect.axis[2]: %f\n", plane->norm_vect.axis[2]);
	printf("data->plane.color.rgb[0]: %i\n", plane->color.rgb[0]);
	printf("data->plane.color.rgb[1]: %i\n", plane->color.rgb[1]);
	printf("data->plane.color.rgb[2]: %i\n", plane->color.rgb[2]);
}


void	fill_struct_pl(t_data *data, double tab[])
{
	static int	i = 0;
	
	// printf("before:\n");
	// print_plane(&data->planes[i], i);

	data->planes[i].origin_vect.axis[0] = tab[0];
	data->planes[i].origin_vect.axis[1] = tab[1];
	data->planes[i].origin_vect.axis[2] = tab[2];
	data->planes[i].norm_vect.axis[0] = tab[3];
	data->planes[i].norm_vect.axis[1] = tab[4];
	data->planes[i].norm_vect.axis[2] = tab[5];
	data->planes[i].color.rgb[0] = tab[6];
	data->planes[i].color.rgb[1] = tab[7];
	data->planes[i].color.rgb[2] = tab[8];

	printf("after:\n");
	print_plane(&data->planes[i], i);

	i++;
}
