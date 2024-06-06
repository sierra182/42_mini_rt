#include "se_mini_struct.h"
#include "x_linear_algebra.h"
#include <math.h>
#include <stdlib.h>

void	add_lightening2(t_add_lightening_params *params) ;

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
void	color_with_ambiant_light(t_color *mesh_color,
			t_ambiant_light *ambiant_light, t_color *new_color);
int		has_shadow(t_data *data, t_ray_vector *normal, t_obj *mesh,
	t_ray *light_ray);
void	add_lightening(t_add_lightening_params *params);
int		get_plane_color(t_get_color_params *params);
void	add_shading( t_ray *ray, t_ray_vector *normal,
			t_color *ambiantly_color, t_color *color);
void	add_self_shadowing(double light_coef, double light_attenuation,
			t_color *color);
void	color_with_light(t_color *mesh_color,
			t_color *light_color, double intensity, t_color *new_color);
void	clamp_255(t_color *color);
int		get_cylinder_color_discs(t_get_color_params *params);
int		is_cylinder_surface_between( t_cylinder *cyl, t_ray_vector *normal,
			double mesh[]);
int		is_in_cyl_height(t_ray_vector *normal, t_cylinder *cyl, double mesh[]);
int	calculate_spotlight_effect(t_calc_spotlight_effect_params *params);
void	calculate_ambiant_effect(t_get_color_params *params,
	t_color *mesh_color, t_ray_vector *normal, t_color *ambiantly_color);

int		is_sphere_surface_between(t_sphere *sphere, t_spotlight *spotlight);

/**========================================================================
 *                           HANDLE_PROJECTION
 *========================================================================**/
void	handle_projection(t_get_color_params *params, t_ray_vector *normal,
	t_ray *light_ray)
{
	t_ray_vector	intersect_point;
	t_ray_vector	cyl_to_intersect;
	double			proj;
	t_ray_vector	proj_vect;
	t_cylinder		*cyl;

	cyl = (t_cylinder *)params->mesh->ref;
	get_intersect_point(params->ray, params->t, &intersect_point);
	subtract_vector(intersect_point.axis, cyl->origin_vect.axis,
		cyl_to_intersect.axis);
	proj = scalar_product(cyl_to_intersect.axis, cyl->axis_vect.axis);
	scale_vector(cyl->axis_vect.axis, proj, proj_vect.axis);
	subtract_vector(cyl_to_intersect.axis, proj_vect.axis, normal->axis);
	normalize_vector(normal->axis);
	if (cyl->which_t == 2)
		symmetrize_vector(normal->axis);
	light_ray->origin_vect = intersect_point;
}

/**========================================================================
 *                   ADD_SHADOW_AND_LIGHTNING_EFFECTS
 *========================================================================**/
static void	add_shadow_and_lightning_effects(t_add_shad_and_light_params *p)
{
	double			light_coef;
	double			light_attenuat;
	t_cylinder		*cyl;
	t_ray_vector	tmp;

	cyl = (t_cylinder *)p->params->mesh->ref;
	cast_vector_mat_ray(&cyl->axis_vect, &tmp);
	// if (has_shadow(p->params->data, p->normal, p->params->mesh, p->light_ray)
	// 	|| is_cylinder_surface_between (cyl, p->normal, p->params->data
	// 		->spotlight.origin_vect.axis) || (!is_in_cyl_height(&tmp, cyl, p
	// 			->params->data->spotlight.origin_vect.axis)
	// 		&& (cyl->which_t == 2)))
	// {
	// 	*p->params->color = *p->ambiantly_color;
	// 	return ;
	// }
	add_lightening(&(t_add_lightening_params){p->light_ray, p->normal,
		&p->params->data->spotlight, p->ambiantly_color, p->params->color,
		&light_attenuat, &light_coef});
	//add_self_shadowing(light_coef, light_attenuat, p->spotlighty_color);
	add_color(p->spotlighty_color, p->ambiantly_color, p->params->color);
	clamp_255(p->params->color);
}
double	calculate_light_attenuation(t_ray *light_ray, double intensity);
double aces_tonemap(double x);
/**========================================================================
 *                           GET_CYLINDER_COLOR_CYL
 *========================================================================**/
void	get_cylinder_color_cyl(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;
	t_cylinder		*cyl;
	t_color			spotlighty_color;

	cyl = (t_cylinder *)params->mesh->ref;
	handle_projection(params, &normal, &light_ray);
	subtract_vector(params->data->spotlight.origin_vect.axis, light_ray
		.origin_vect.axis, light_ray.dir_vect.axis);

	
	// double	light_attenuat;
	// t_ray	light_ray_cpy;
	// double 	light_coef;

	// light_ray_cpy = light_ray;
	// normalize_vector(light_ray_cpy.dir_vect.axis);
	// light_coef = scalar_product(light_ray_cpy.dir_vect.axis,
	// 		normal.axis);
	// normalize_zero_one(&light_coef, 1);
	// 	light_coef = aces_tonemap(light_coef);
	// light_attenuat = calculate_light_attenuation(&light_ray,
	// 	light_coef * params->data->spotlight.intensity);

	// color_with_light(&cyl->color, &params->data->ambiant_light.color,
	// 	params->data->ambiant_light.intensity, &ambiantly_color);
	// color_with_light(&cyl->color, &params->data->spotlight.color, params->data->spotlight.intensity * light_attenuat, &spotlighty_color);
	// // add_shading(params->ray, &normal, &ambiantly_color, &ambiantly_color);
	// // add_shading(params->ray, &normal, &spotlighty_color, &spotlighty_color);
	// add_shadow_and_lightning_effects(&(t_add_shad_and_light_params)
	// {params, &normal, &light_ray, &ambiantly_color, &spotlighty_color});



	t_ray_vector	tmp;
	cast_vector_mat_ray(&cyl->axis_vect, &tmp);
	normalize_vector(tmp.axis);
	calculate_ambiant_effect(params, &cyl->color, &normal,
		&ambiantly_color);
	if (has_shadow(params->data, &normal, params->mesh, &light_ray)
		|| is_cylinder_surface_between (cyl, &normal, params->data
			->spotlight.origin_vect.axis) || (!is_in_cyl_height(&tmp, cyl, 
				params->data->spotlight.origin_vect.axis)
			&& (cyl->which_t == 2)))
	{
		*params->color = ambiantly_color;
		return ;
	}
	calculate_spotlight_effect(&(t_calc_spotlight_effect_params)
		{params, &cyl->color, &normal, &spotlighty_color, &light_ray});
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	clamp_255(params->color);








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
		{data, ray, obj->t, obj, color});
	}
	if (cyl->cyl_or_discs == discs)
	{
		get_cylinder_color_discs(&(t_get_color_params)
		{data, ray, obj->t, obj, color});
	}
}
