#include "se_mini_struct_bonus.h"
#include "x_linear_algebra_bonus.h"
#include <stdio.h>

double	get_bump_coef(double **bump_map, double u, double v);

void	calculate_tangent(t_ray_vector *normal, t_ray_vector *T)
{
	T->axis[0] = -normal->axis[2];
	T->axis[1] = 0;
	T->axis[2] = normal->axis[0];
	self_normalize_vector(T->axis);
}

void	calculate_bitangent(t_ray_vector *N, t_ray_vector *T, t_ray_vector *B)
{
	B->axis[0] = N->axis[1] * T->axis[2] - N->axis[2] * T->axis[1];
	B->axis[1] = N->axis[2] * T->axis[0] - N->axis[0] * T->axis[2];
	B->axis[2] = N->axis[0] * T->axis[1] - N->axis[1] * T->axis[0];
	self_normalize_vector(B->axis);
}

void	calculate_bump_derivatives(t_calculate_bump_derivatives_params *p)
{
	double	bump_coef;
	double	bump_coef_u;
	double	bump_coef_v;

	bump_coef = get_bump_coef(p->bump_map, p->u, p->v);
	bump_coef_u = get_bump_coef(p->bump_map, p->u + (1.0 / XPM_size), p->v);
	bump_coef_v = get_bump_coef(p->bump_map, p->u, p->v + (1.0 / XPM_size));
	*p->du = (bump_coef_u - bump_coef) / (1.0 / XPM_size);
	*p->dv = (bump_coef_v - bump_coef) / (1.0 / XPM_size);
}

/**========================================================================
 *                           apply_bump_mapping
 * change scale value for texturization "intensity"
 *========================================================================**/
void	apply_bump_mapping(t_ray_vector *normal, double u, double v,
	double **bump_map)
{
	t_ray_vector	t;
	t_ray_vector	b;
	double			du;
	double			dv;
	double			scale;

	scale = 0.001;
	calculate_tangent(normal, &t);
	calculate_bitangent(normal, &t, &b);
	calculate_bump_derivatives(&(t_calculate_bump_derivatives_params)
	{u, v, &du, &dv, bump_map});
	normal->axis[0] = normal->axis[0] + scale * (du * t.axis[0] + dv
			* b.axis[0]);
	normal->axis[1] = normal->axis[1] + scale * (du * t.axis[1] + dv
			* b.axis[1]);
	normal->axis[2] = normal->axis[2] + scale * (du * t.axis[2] + dv
			* b.axis[2]);
	self_normalize_vector(normal->axis);
}
