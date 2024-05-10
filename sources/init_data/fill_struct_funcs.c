#include "fill_struct_funcs.h"

void	fill_struct_a(t_data *data, double tab[])
{
	data->ambiant_light.intensity = tab[0];
	data->ambiant_light.color.rgb[0] = tab[1];
	data->ambiant_light.color.rgb[1] = tab[2];
	data->ambiant_light.color.rgb[2] = tab[3];
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
	data->spotlight.origin_vect.axis[0] = tab[0];
	data->spotlight.origin_vect.axis[1] = tab[1];
	data->spotlight.origin_vect.axis[2] = tab[2];
	data->spotlight.origin_vect.axis[3] = 1;
	data->spotlight.intensity = tab[3];
	data->spotlight.bulb.color.rgb[0] = 255;
	data->spotlight.bulb.color.rgb[1] = 255;
	data->spotlight.bulb.color.rgb[2] = 255;
	data->spotlight.bulb.diameter = 1;
	data->spotlight.bulb.square_radius = (data->spotlight.bulb.diameter / 2)
		* (data->spotlight.bulb.diameter / 2);
	data->spotlight.bulb.origin_vect = data->spotlight.origin_vect;
}

void	fill_struct_sp(t_data *data, double tab[])
{
	static int	i = 0;

	data->spheres[i].origin_vect.axis[0] = tab[0];
	data->spheres[i].origin_vect.axis[1] = tab[1];
	data->spheres[i].origin_vect.axis[2] = tab[2];
	data->spheres[i].origin_vect.axis[3] = 1;
	data->spheres[i].diameter = tab[3];
	data->spheres[i].square_radius = tab[3] / 2 * tab[3] / 2;
	data->spheres[i].color.rgb[0] = tab[4];
	data->spheres[i].color.rgb[1] = tab[5];
	data->spheres[i].color.rgb[2] = tab[6];	
	i++;
}

void	print_cylinder(t_cylinder *cylinder)
{
	printf("data->cylinders.origin_vect.axis[0]: %f\n", cylinder->origin_vect.axis[0]);
	printf("data->cylinders.origin_vect.axis[1]: %f\n", cylinder->origin_vect.axis[1]);
	printf("data->cylinders.origin_vect.axis[2]: %f\n", cylinder->origin_vect.axis[2]);
	printf("data->cylinders.axis_vect.axis[0]: %f\n", cylinder->axis_vect.axis[0]);
	printf("data->cylinders.axis_vect.axis[1]: %f\n", cylinder->axis_vect.axis[1]);
	printf("data->cylinders.axis_vect.axis[2]: %f\n", cylinder->axis_vect.axis[2]);
	printf("data->cylinders.diameter: %f\n", cylinder->diameter);
	printf("data->cylinders.height: %f\n", cylinder->height);
	printf("data->cylinders.color.rgb[0]: %i\n", cylinder->color.rgb[0]);
	printf("data->cylinders.color.rgb[1]: %i\n", cylinder->color.rgb[1]);
	printf("data->cylinders.color.rgb[2]: %i\n", cylinder->color.rgb[2]);


}



void	fill_struct_cy(t_data *data, double tab[])
{
	static int	i = 0;

	data->cylinders[i].origin_vect.axis[0] = tab[0];
	data->cylinders[i].origin_vect.axis[1] = tab[1];
	data->cylinders[i].origin_vect.axis[2] = tab[2];
	data->cylinders[i].axis_vect.axis[0] = tab[3];
	data->cylinders[i].axis_vect.axis[1] = tab[4];
	data->cylinders[i].axis_vect.axis[2] = tab[5];
	data->cylinders[i].diameter = tab[6];
	data->cylinders[i].radius = tab[6] / 2;
	data->cylinders[i].square_radius = (tab[6] / 2) * (tab[6] / 2);
	data->cylinders[i].height = tab[7];
	data->cylinders[i].color.rgb[0] = tab[8];
	data->cylinders[i].color.rgb[1] = tab[9];
	data->cylinders[i].color.rgb[2] = tab[10];
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
	
	data->planes[i].origin_vect.axis[0] = tab[0];
	data->planes[i].origin_vect.axis[1] = tab[1];
	data->planes[i].origin_vect.axis[2] = tab[2];
	data->planes[i].norm_vect.axis[0] = tab[3];
	data->planes[i].norm_vect.axis[1] = tab[4];
	data->planes[i].norm_vect.axis[2] = tab[5];
	data->planes[i].color.rgb[0] = tab[6];
	data->planes[i].color.rgb[1] = tab[7];
	data->planes[i].color.rgb[2] = tab[8];

	i++;
}
