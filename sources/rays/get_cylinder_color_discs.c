#include "x_mini_struct.h"
#include "x_linear_algebra.h"

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
void	color_with_light(t_color *mesh_color,
			t_color *light_color, double intensity, t_color *new_color);
void	limit_to_255(t_color *color);
void	add_lightening(t_add_lightening_params *params);
void	add_self_shadowing(double light_coef, double light_attenuation,
			t_color *color);
void	add_shading( t_ray *ray, t_ray_vector *normal,
			t_color *ambiantly_color, t_color *color);
int		has_shadow(t_data *data, void *mesh, t_ray *light_ray);

/**========================================================================
 *                           ADD_SHADING_AND_LIGNTENING_EFFECTS
 *========================================================================**/
void static	add_shading_and_ligntening_effects(t_get_color_params *params,
	t_ray_vector *normal, double *light_dot_normal, t_ray *light_ray)
{
	t_color			ambiantly_color;
	t_color			spotlighty_color;
	double			light_attenuat;
	double			light_coef;
	t_cylinder		*cyl;

	cyl = ((t_cylinder *) params->mesh->ref);
	color_with_light(&cyl->color, &params->data->ambiant_light.color, params
		->data->ambiant_light.intensity, &ambiantly_color);
	color_with_light(&cyl->color, &(t_color){.rgb[0] = 255, .rgb[1] = 255,
		.rgb[2] = 255}, params->data->spotlight.intensity, &spotlighty_color);
	add_shading(params->ray, normal, &ambiantly_color, &ambiantly_color);
	add_shading(params->ray, normal, &spotlighty_color, &spotlighty_color);
	if (has_shadow(params->data, params->mesh, light_ray)
		|| (*light_dot_normal > 0.0))
		*params->color = ambiantly_color;
	add_lightening(&(t_add_lightening_params){light_ray, normal, &params
		->data->spotlight, &ambiantly_color, params->color,
		&light_attenuat, &light_coef});
	add_self_shadowing(light_coef, light_attenuat, &spotlighty_color);
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	limit_to_255(params->color);
}

/**========================================================================
 *                           GET_CYLINDER_COLOR_DISCS
 *========================================================================**/
void	get_cylinder_color_discs(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	double			light_dot_normal;
	double			view_dot_normal;
	t_cylinder		*cyl;

	cyl = ((t_cylinder *) params->mesh->ref);
	cast_vector_mat_ray(&cyl->axis_vect, &normal);
	get_intersect_point(params->ray, params->t, &light_ray.origin_vect);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	light_dot_normal = scalar_product(normal.axis, light_ray.dir_vect.axis);
	if (light_dot_normal > 0)
		symmetrize_vector(normal.axis);
	view_dot_normal = scalar_product(normal.axis, params->ray->dir_vect.axis);
	if (view_dot_normal > 0)
		symmetrize_vector(normal.axis);
	add_shading_and_ligntening_effects(params, &normal, &light_dot_normal,
		&light_ray);
}
