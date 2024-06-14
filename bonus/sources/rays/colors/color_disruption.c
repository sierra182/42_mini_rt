#include "get_sph_pl_bck_color_bonus.h"
void	clamp_rgb_0(t_color *color);
#include <math.h>

// void cartesian_to_spherical(t_ray_vector *point, float *theta, float *phi)
// {
// 	float r;
	
// 	r = sqrt(point->axis[0]* point->axis[0]+ point->axis[1] * point->axis[1] + point->axis[2] * point->axis[2]);
// 	*theta = acos(point->axis[2] / r);
// 	*phi = atan2(point->axis[1], point->axis[0]);
// }

void calculate_uv(t_ray_vector point, double *u, double *v) {
	double theta;
	double phi;
	
	theta = atan2(point.axis[2], point.axis[0]);
	phi = asin(point.axis[1]);

	*u = 0.5 + theta / (2 * M_PI);
	*v = 0.5 - phi / M_PI;
}

void checker_color(double u, double v, int checker_size, t_color *color)
{
	int u_index = (int)(u * checker_size);
	int v_index = (int)(v * checker_size);
	int	is_checker;
		
	is_checker = (u_index % 2 == v_index % 2);
	if (is_checker)
	{
		color->rgb[0] *= 0.3;
		color->rgb[1] *= 0.3;
		color->rgb[2] *= 0.3;
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
	checker_color(u, v, size, params->color);
}