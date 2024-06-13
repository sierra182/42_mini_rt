#include "fill_struct_funcs_2_bonus.h"

char *get_bmpath(t_data *data, int index)
{
	char *bmpath;

	bmpath = data->bump_map_paths[index];
	return bmpath;
}

/**========================================================================
 *                           FILL_STRUCT_SP
 *========================================================================**/
void	fill_struct_sp(t_data *data, double tab[])
{
	static int	i = 0;

	data->spheres[i].origin_vect.axis[0] = tab[0];
	data->spheres[i].origin_vect.axis[1] = tab[1];
	data->spheres[i].origin_vect.axis[2] = tab[2];
	data->spheres[i].origin_vect.axis[3] = 1;
	data->spheres[i].diameter = tab[3];
	data->spheres[i].radius = data->spheres[i].diameter * 0.5;
	data->spheres[i].square_radius = data->spheres[i].radius
		* data->spheres[i].radius;
	data->spheres[i].color.rgb[0] = tab[4];
	data->spheres[i].color.rgb[1] = tab[5];
	data->spheres[i].color.rgb[2] = tab[6];
	if (tab[7] == -42)
	{
		data->spheres[i].checkerboard = 1;
	}
	else if ((int)tab[7] != 1024)
	{
		data->planes[i].bump_map_path = get_bmpath(data, (int)tab[7]);
		// printf("sphere bump map path: %s\n", data->planes[i].bump_map_path);
	}
	else
		data->spheres[i].checkerboard = 0;
	data->spheres[i].which_t = 0;
	data->spheres[i].t1 = 0.0;
	data->spheres[i].t2 = 0.0;
	i++;
}

/**========================================================================
 *                           FILL_STRUCT_CY
 *========================================================================**/
void	fill_struct_cy(t_data *data, double tab[])
{
	static int	i = 0;

	data->cylinders[i].origin_vect.axis[0] = tab[0];
	data->cylinders[i].origin_vect.axis[1] = tab[1];
	data->cylinders[i].origin_vect.axis[2] = tab[2];
	data->cylinders[i].origin_vect.axis[3] = 1;
	data->cylinders[i].axis_vect.axis[0] = tab[3];
	data->cylinders[i].axis_vect.axis[1] = tab[4];
	data->cylinders[i].axis_vect.axis[2] = tab[5];
	data->cylinders[i].diameter = tab[6];
	data->cylinders[i].radius = data->cylinders[i].diameter * 0.5;
	data->cylinders[i].square_radius = data->cylinders[i].radius
		* data->cylinders[i].radius;
	data->cylinders[i].height = tab[7];
	data->cylinders[i].color.rgb[0] = tab[8];
	data->cylinders[i].color.rgb[1] = tab[9];
	data->cylinders[i].color.rgb[2] = tab[10];
	data->cylinders[i].which_t = 0;
	data->cylinders[i].t1 = 0.0;
	data->cylinders[i].t2 = 0.0;
	i++;
}

/**========================================================================
 *                           FILL_STRUCT_PL
 *========================================================================**/
void	fill_struct_pl(t_data *data, double tab[])
{
	static int	i = 0;

	data->planes[i].origin_vect.axis[0] = tab[0];
	data->planes[i].origin_vect.axis[1] = tab[1];
	data->planes[i].origin_vect.axis[2] = tab[2];
	data->planes[i].origin_vect.axis[3] = 1;
	data->planes[i].norm_vect.axis[0] = tab[3];
	data->planes[i].norm_vect.axis[1] = tab[4];
	data->planes[i].norm_vect.axis[2] = tab[5];
	data->planes[i].color.rgb[0] = tab[6];
	data->planes[i].color.rgb[1] = tab[7];
	data->planes[i].color.rgb[2] = tab[8];
	if (tab[9] == -42)
	{
		data->planes[i].checkerboard = 1;
	}
	else if ((int)tab[9] != 1024)
	{
		data->planes[i].bump_map_path = get_bmpath(data, (int)tab[9]);
		// printf("plane bump map path: %s\n", data->planes[i].bump_map_path);
	}
	else
		data->planes[i].checkerboard = 0;
	i++;
}

/**========================================================================
 *                           FILL_STRUCT_L
 *========================================================================**/
void	fill_struct_l(t_data *data, double tab[])
{
	static int	i = 0;

	data->spotlights[i].origin_vect.axis[0] = tab[0];
	data->spotlights[i].origin_vect.axis[1] = tab[1];
	data->spotlights[i].origin_vect.axis[2] = tab[2];
	data->spotlights[i].origin_vect.axis[3] = 1;
	data->spotlights[i].intensity = tab[3];
	data->spotlights[i].color.rgb[0] = tab[4];
	data->spotlights[i].color.rgb[1] = tab[5];
	data->spotlights[i].color.rgb[2] = tab[6];
	data->spotlights[i].bulb.color = data->spotlight.color;
	data->spotlights[i].bulb.diameter = 1;
	data->spotlights[i].bulb.radius = data->spotlight.bulb.diameter * 0.5;
	data->spotlights[i].bulb.square_radius = data->spotlight.bulb.radius
		* data->spotlights[i].bulb.radius;
	data->spotlights[i].bulb.origin_vect = data->spotlight.origin_vect;
	i++;
}

void	print_triangle(t_triangle *triangle)
{
	printf("triangle: \n");
	printf("%f\n", triangle->point_a.axis[0]);
	printf("%f\n", triangle->point_a.axis[1]);
	printf("%f\n", triangle->point_a.axis[2]);
	printf("%f\n", triangle->point_b.axis[0]);
	printf("%f\n", triangle->point_b.axis[1]);
	printf("%f\n", triangle->point_b.axis[2]);
	printf("%f\n", triangle->point_c.axis[0]);
	printf("%f\n", triangle->point_c.axis[1]);
	printf("%f\n", triangle->point_c.axis[2]);
	printf("%i\n", triangle->color.rgb[0]);
	printf("%i\n", triangle->color.rgb[1] );
	printf("%i\n", triangle->color.rgb[2] );
}

void	fill_struct_tr(t_data *data, double tab[])
{
	static int	i = 0;
	data->triangles[i].point_a.axis[0] = tab[0];
	data->triangles[i].point_a.axis[1] = tab[1];
	data->triangles[i].point_a.axis[2] = tab[2];
	data->triangles[i].point_b.axis[0] = tab[3];
	data->triangles[i].point_b.axis[1] = tab[4];
	data->triangles[i].point_b.axis[2] = tab[5];
	data->triangles[i].point_c.axis[0] = tab[6];
	data->triangles[i].point_c.axis[1] = tab[7];
	data->triangles[i].point_c.axis[2] = tab[8];
	data->triangles[i].color.rgb[0] = tab[9];
	data->triangles[i].color.rgb[1] = tab[10];
	data->triangles[i].color.rgb[2] = tab[11];
	// print_triangle(&data->triangles[i]);
	i++;
}
