#include "x_mini_struct.h"
#include "x_linear_algebra.h"

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
void	color_with_ambiant_light(t_color *mesh_color,
			t_ambiant_light *ambiant_light, t_color *new_color);
int		has_shadow(t_data *data, void *mesh, t_ray *light_ray);
void	add_lightening(t_add_lightening_params *params);
void	get_plane_color(t_get_color_params *params);
void	add_shading( t_ray *ray, t_ray_vector *normal,
			t_color *ambiantly_color, t_color *color);
void	add_self_shadowing(double light_coef, double light_attenuation,
			t_color *color);
void	color_with_light(t_color *mesh_color,
			t_color *light_color, double intensity, t_color *new_color);
void	limit_to_255(t_color *color);
int		get_cylinder_color_discs(t_get_color_params *params);

/**========================================================================
 *                           ADD_SHADING_AND_LIGNTENING_EFFECTS
 *========================================================================**/
void	add_shading_and_ligntening_effects(t_get_color_params *params,
	t_ray_vector *normal, t_ray *light_ray)
{
	t_color			spotlighty_color;
	double			light_attenuat;
	double			light_coef;
	t_color			ambiantly_color;
	t_cylinder		*cyl;

	cyl = (t_cylinder *)params->mesh;
	color_with_light(&cyl->color, &params->data->ambiant_light.color, params
		->data->ambiant_light.intensity, &ambiantly_color);
	color_with_light(&cyl->color, &(t_color){.rgb[0] = 255, .rgb[1] = 255,
		.rgb[2] = 255}, params->data->spotlight.intensity,
		&spotlighty_color);
	add_shading(params->ray, normal, &ambiantly_color, &ambiantly_color);
	add_shading(params->ray, normal, &spotlighty_color, &spotlighty_color);
	if (has_shadow(params->data, cyl, light_ray))
		*params->color = ambiantly_color;
	add_lightening(&(t_add_lightening_params){light_ray, normal, &params
		->data->spotlight, &ambiantly_color, params->color,
		&light_attenuat, &light_coef});
	add_self_shadowing(light_coef, light_attenuat, &spotlighty_color);
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	limit_to_255(params->color);
}

void	handle_projection()
{

}

/**========================================================================
 *                           GET_CYLINDER_COLOR_CYL
*========================================================================**/
void	get_cylinder_color_cyl(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	t_cylinder		*cyl;
	t_ray_vector	intersect_point;
	t_ray_vector	cyl_to_intersect;
	double			proj;
	t_ray_vector	proj_vect;

	cyl = (t_cylinder *)params->mesh;
	get_intersect_point(params->ray, params->t, &intersect_point);
	subtract_vector(intersect_point.axis, cyl->origin_vect.axis,
		cyl_to_intersect.axis);

	handle_projection();
	proj = scalar_product(cyl_to_intersect.axis, cyl->axis_vect.axis);
	scale_vector(cyl->axis_vect.axis, proj, proj_vect.axis);
	subtract_vector(cyl_to_intersect.axis, proj_vect.axis, normal.axis);
	normalize_vector(normal.axis);
	if (((t_cylinder *)params->mesh)->which_t == 2)
		symmetrize_vector(normal.axis);
	light_ray.origin_vect = intersect_point;
	subtract_vector(params->data->spotlight.origin_vect.axis, light_ray
		.origin_vect.axis, light_ray.dir_vect.axis);
	add_shading_and_ligntening_effects(params, &normal, &light_ray);
}

/**========================================================================
 *                           GET_CYLINDER_COLOR
 *========================================================================**/
void	get_cylinder_color(t_data *data, t_ray *ray, t_obj *obj,
		t_color *color)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)obj->ref;
	if (cyl->cyl_or_discs == cylinder)
	{
		get_cylinder_color_cyl(&(t_get_color_params)
		{data, ray, obj->t, obj->ref, color});
	}
	if (cyl->cyl_or_discs == discs)
	{
		get_cylinder_color_discs(&(t_get_color_params)
		{data, ray, obj->t, obj->ref, color});
	}
}
