#include "se_mini_struct.h"
#include "x_linear_algebra.h"

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
void	color_with_light(t_color *mesh_color,
			t_color *light_color, double intensity, t_color *new_color);
void	clamp_255(t_color *color);
void	add_lightening(t_add_lightening_params *params);
void	add_self_shadowing(double light_coef, double light_attenuation,
			t_color *color);
void	add_shading( t_ray *ray, t_ray_vector *normal,
			t_color *ambiantly_color, t_color *color);
int		has_shadow(t_data *data, t_ray_vector *normal, void *mesh,
			t_ray_pack *light_ray);
int		are_light_and_cam_in_different_cyl_space(t_ray_vector *normal,
			t_spotlight *light, t_cylinder *cyl, t_cam *cam);
int		calculate_spotlight_effect(t_calc_spotlight_effect_params *params);
void	calculate_ambiant_effect(t_get_color_params *params,
			t_color *mesh_color, t_ray_vector *normal,
			t_color *ambiantly_color);
int		is_sphere_surface_between(t_sphere *sphere, t_spotlight *spotlight);
void	calculate_ray_pack(t_ray_pack *ray_pack);

/**========================================================================
 *                           ADD_LIGHTNING_EFFECTS
 *========================================================================**/
// static void	add_lightning_effects(t_add_shad_and_light_params *p)
// {
// 	double			light_attenuat;
// 	double			light_coef;
// 	t_cylinder		*cyl;

// 	cyl = ((t_cylinder *) p->params->mesh->ref);
// 	light_coef = scalar_product(p->normal->axis, p->light_ray->dir_vect.axis);
// 	if (has_shadow(p->params->data, p->normal, p->params->mesh, p->light_ray)
// 		|| light_coef < 0.0 || are_light_and_cam_in_different_cyl_space
// 		(p->normal, &p->params->data->spotlight, cyl, &p->params->data->cam))
// 	{
// 		*p->params->color = *p->ambiantly_color;
// 		return ;
// 	}
// 	add_lightening(&(t_add_lightening_params){p->light_ray, p->normal,
// 		&p->params->data->spotlight, p->ambiantly_color, p->params->color,
// 		&light_attenuat, &light_coef});
// 	add_self_shadowing(light_coef, light_attenuat, p->spotlighty_color);
// 	add_color(p->spotlighty_color, p->ambiantly_color, p->params->color);
// 	clamp_255(p->params->color);
// }

/**========================================================================
 *                           HANDLE_NORMAL_SYMMETRIZATION
 *========================================================================**/
void	handle_normal_symmetrization(t_get_color_params *params, t_ray_vector
*normal, t_ray *light_ray)
{
	double			light_dot_normal;
	double			view_dot_normal;
	t_cylinder		*cyl;

	cyl = ((t_cylinder *) params->mesh->ref);
	view_dot_normal = scalar_product(normal->axis, params->ray->dir_vect.axis);
	if (view_dot_normal > 0.0)
		symmetrize_vector(normal->axis);
	light_dot_normal = scalar_product(normal->axis, light_ray->dir_vect.axis);
	if (light_dot_normal < 0 && cyl->which_t == 2)
		symmetrize_vector(normal->axis);
}

/**========================================================================
 *                           GET_CYLINDER_COLOR_DISCS
 *========================================================================**/
int	get_cylinder_color_discs(t_get_color_params *params)
{
	t_ray_pack			light_ray;
	t_color			ambiantly_color;
	t_color			spotlighty_color;
	t_cylinder		*cyl;
	double			light_coef;

	cyl = ((t_cylinder *) params->mesh->ref);
	cast_vector_mat_ray(&cyl->axis_vect, params->normal);
	self_normalize_vector(params->normal->axis);
	get_intersect_point(params->ray, params->t, &light_ray.ray.origin_vect);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray.ray.origin_vect.axis, light_ray.ray.dir_vect.axis);
		calculate_ray_pack(&light_ray);
	handle_normal_symmetrization(params, params->normal, &light_ray.ray);
	calculate_ambiant_effect(params, &cyl->color, params->normal,
		&ambiantly_color);
	light_coef = scalar_product(params->normal->axis, light_ray.ray.dir_vect.axis);
	if (has_shadow(params->data, params->normal, params->mesh, &light_ray)
		|| light_coef < 0.0 || are_light_and_cam_in_different_cyl_space
		(params->normal, &params->data->spotlight, cyl, &params->data->cam))
		return (*params->color = ambiantly_color, 0);
	calculate_spotlight_effect(&(t_calc_spotlight_effect_params)
	{params, &cyl->color, params->normal, &spotlighty_color, &light_ray.ray});
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	clamp_255(params->color);
	return (0);
}
