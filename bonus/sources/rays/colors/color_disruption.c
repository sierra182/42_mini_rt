#include "get_sph_pl_bck_color_bonus.h"
void	clamp_rgb_0(t_color *color);
#include <math.h>

void cartesian_to_spherical(t_ray_vector *point, float *theta, float *phi)
{
	float r;
	
	r = sqrt(point->axis[0]* point->axis[0]+ point->axis[1] * point->axis[1] + point->axis[2] * point->axis[2]);
	*theta = acos(point->axis[2] / r);
	*phi = atan2(point->axis[1], point->axis[0]);
}

int is_checkerboard(t_ray_vector point, float size)
{
	float theta;
	float phi;
	int check_theta;
	int check_phi;

	cartesian_to_spherical(&point, &theta, &phi);

	// Convertir theta et phi en indices de damier
	check_theta = (int)(theta / size) % 2;
	check_phi = (int)(phi / size) % 2;

	// Alterner les couleurs selon les indices
	return (check_theta + check_phi) % 2 == 0;
}

void	checker_board_modif(t_get_color_params *params, t_color *color_altered, t_ray_vector *i_point)
{
	t_sphere		*sphere;

	int i;

	sphere = (t_sphere *) params->mesh->ref;
	if (sphere->checkerboard == 0)
		return ;
	i = 0;
	while (i < 3)
	{
		// printf("color->rgb[%d] = %d\n", i, sphere->color.rgb[i]);
		color_altered->rgb[i] = sphere->color.rgb[i];
		i++;
	}
		// color_altered->rgb[0] -= 50;
		// color_altered->rgb[1] -= 50;
		// color_altered->rgb[2] -= 50;

	// sphere->color.rgb[0] -= 50;
	// sphere->color.rgb[1] -= 50;
	// sphere->color.rgb[2] -= 50;
	if (is_checkerboard(*i_point, 0.05))
	{
		*params->color = *color_altered;
		apply_aces_tonemap(params->color);
		return ;
	}
	params->color->rgb[0] -= 50;
	params->color->rgb[1] -= 50;
	params->color->rgb[2] -= 50;

	clamp_rgb_0(params->color);
}


void calculate_uv(t_ray_vector point, double *u, double *v) {
	double theta;
	double phi;
	
	theta = atan2(point.axis[2], point.axis[0]);
	phi = asin(point.axis[1]);
	*u = 0.5 + theta / (2 * M_PI);
	*v = 0.5 - phi / M_PI;
}

void checker_color(double u, double v, int checker_size, int *rgb)
{
	int u_index = (int)(u * checker_size);
	int v_index = (int)(v * checker_size);
	int	is_checker;
	is_checker = (u_index % 2 == v_index % 2);

	
	if (is_checker)
	{
		rgb[0] = 0;
		rgb[1] = 0;
		rgb[2] = 0;
	}
	else
	{
		rgb[0] = 255;
		rgb[1] = 255;
		rgb[2] = 255;
	}
}

void	checker_board_modif_uv(t_get_color_params *params, t_ray_pack light_ray, int size)
{
	double u;
	double v;
	t_sphere		*sphere;

	sphere = (t_sphere *) params->mesh->ref;
	if (sphere->checkerboard == 0)
		return ;
	calculate_uv(*params->normal, &u, &v);
	checker_color(u, v, size, params->color->rgb);
}