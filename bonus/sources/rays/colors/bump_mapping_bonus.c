#include "se_mini_struct_bonus.h"
#include "x_linear_algebra_bonus.h"
#include <stdio.h>

double	get_bump_coef(t_sphere *sphere, double **bump_map, double u, double v);
void	calculate_tangent(t_ray_vector *normal, t_ray_vector *t);
void	calculate_bitangent(t_ray_vector *n, t_ray_vector *t, t_ray_vector *b);
void	calculate_bump_derivatives(t_calculate_bump_derivatives_params *p);

/**========================================================================
 *                           apply_bump_mapping
 * change scale value for texturization "intensity"
 *========================================================================**/
void	apply_bump_mapping(t_ray_vector *normal, double u, double v,
	t_get_color_params *params)
{
	t_ray_vector	t;
	t_ray_vector	b;
	double			du;
	double			dv;
	double			scale;
	t_sphere	*sphere;

	sphere = (t_sphere *) params->mesh->ref;

	double **bump_map = params->data->bump_maps[sphere->bump_map_nbr];
	scale = 0.001;
	calculate_tangent(normal, &t);
	calculate_bitangent(normal, &t, &b);
	calculate_bump_derivatives(&(t_calculate_bump_derivatives_params)
	{u, v, &du, &dv, bump_map, sphere});
	normal->axis[0] = normal->axis[0] + scale * (du * t.axis[0] + dv
			* b.axis[0]);
	normal->axis[1] = normal->axis[1] + scale * (du * t.axis[1] + dv
			* b.axis[1]);
	normal->axis[2] = normal->axis[2] + scale * (du * t.axis[2] + dv
			* b.axis[2]);
	self_normalize_vector(normal->axis);
}

/**========================================================================
 *                           CALCULATE_TANGENT
 *========================================================================**/
void	calculate_tangent(t_ray_vector *normal, t_ray_vector *t)
{
	t->axis[0] = -normal->axis[2];
	t->axis[1] = 0;
	t->axis[2] = normal->axis[0];
	self_normalize_vector(t->axis);
}

/**========================================================================
 *                           CALCULATE_BITANGENT
 *========================================================================**/
void	calculate_bitangent(t_ray_vector *n, t_ray_vector *t, t_ray_vector *b)
{
	b->axis[0] = n->axis[1] * t->axis[2] - n->axis[2] * t->axis[1];
	b->axis[1] = n->axis[2] * t->axis[0] - n->axis[0] * t->axis[2];
	b->axis[2] = n->axis[0] * t->axis[1] - n->axis[1] * t->axis[0];
	self_normalize_vector(b->axis);
}

/**========================================================================
 *                           CALCUATE_BUMP_DERIVATIVES
 *========================================================================**/
void	calculate_bump_derivatives(t_calculate_bump_derivatives_params *p)
{
	double	bump_coef;
	double	bump_coef_u;
	double	bump_coef_v;
	int		xpm_size_x;
	int		xpm_size_y;
	t_sphere	*sphere;

	sphere = (t_sphere *) p->sphere;

	xpm_size_x = p->sphere->xpm_size_x;
	xpm_size_y = p->sphere->xpm_size_y;
	bump_coef = get_bump_coef(sphere, p->bump_map, p->u, p->v);
	bump_coef_u = get_bump_coef(sphere, p->bump_map, p->u + (1.0 / xpm_size_x), p->v);
	bump_coef_v = get_bump_coef(sphere, p->bump_map, p->u, p->v + (1.0 / xpm_size_y));
	*p->du = (bump_coef_u - bump_coef) / (1.0 / xpm_size_x);
	*p->dv = (bump_coef_v - bump_coef) / (1.0 / xpm_size_y);
}
