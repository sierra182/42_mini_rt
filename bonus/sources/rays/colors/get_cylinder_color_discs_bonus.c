#include "get_cylinder_color_discs_bonus.h"
int	calculate_spotlight_effect3(t_spotlight *spotlight, t_calc_spotlight_effect_params *params);

void	add_disc_spotlights_effect(t_get_color_params *params,
	t_ray_vector *normal, t_color *spotlighties_color, t_color *mesh_color, t_ray_pack	*light_ray)
{	
	t_color		spotlighty_color;
	double		light_coef;
	int			i;

	*spotlighties_color = (t_color){.rgb[0] = 0, .rgb[1] = 0, .rgb[2] = 0};
	i = -1;
	while (++i < params->data->sl_nbr)
		{
		subtract_vector(params->data->spotlights[i].origin_vect.axis,
			light_ray->ray.origin_vect.axis, light_ray->ray.dir_vect.axis);
		calculate_ray_pack(light_ray);
		handle_normal_symmetrization(params, params->normal, &light_ray->ray);
		light_coef = scalar_product(params->normal->axis,
				light_ray->ray.dir_vect.axis);
		// calculate_ambiant_effect(params, &mesh_color, params->normal,
		// 	&ambiantly_color);
		if (is_ambianced_only(&params->data->spotlights[i], params, light_ray, &light_coef))
			continue ;
		calculate_spotlight_effect3(&params->data->spotlights[i],
			&(t_calc_spotlight_effect_params)
		{params, mesh_color, normal, &spotlighty_color, light_ray});

	add_color(spotlighties_color, &spotlighty_color, spotlighties_color);
		// compute_light_ray(&params->data->spotlights[i], params,
		// 	light_ray);	
		// if (has_shadow(params->data, params->mesh, light_ray)
		// 	|| scalar_product(normal->axis, light_ray->ray.dir_vect.axis) < 1e-3)	
		// 	continue;
		// calculate_spotlight_effect3(&params->data->spotlights[i],
		// 	&(t_calc_spotlight_effect_params)
		// {params, mesh_color, normal, &spotlighty_color, light_ray});
		// add_color(spotlighties_color, &spotlighty_color, spotlighties_color);
	}
}
/**========================================================================
 *                           GET_CYLINDER_COLOR_DISCS
 *========================================================================**/
void	get_cylinder_color_discs(t_get_color_params *params)
{
	t_ray_pack	light_ray;
	t_color		ambiantly_color;
	t_color		spotlighties_color;
	t_cylinder	*cyl;
	double			view_dot_normal;

	cyl = ((t_cylinder *) params->mesh->ref);
	cast_vector_mat_ray(&cyl->axis_vect, params->normal);
	self_normalize_vector(params->normal->axis);
	get_intersect_point(params->ray, params->t, &light_ray.ray.origin_vect);
	view_dot_normal = scalar_product(params->normal->axis, params->ray->dir_vect.axis);
	if (view_dot_normal > 0.0)
		symmetrize_vector(params->normal->axis);
	calculate_ambiant_effect(params, &cyl->color, params->normal,
			&ambiantly_color);
	add_disc_spotlights_effect(params, params->normal, &spotlighties_color,
		&cyl->color, &light_ray);
	// subtract_vector(params->data->spotlight.origin_vect.axis,
	// 	light_ray.ray.origin_vect.axis, light_ray.ray.dir_vect.axis);
	// calculate_ray_pack(&light_ray);//!
	// handle_normal_symmetrization(params, params->normal, &light_ray.ray);
	// calculate_ambiant_effect(params, &cyl->color, params->normal,
	// 	&ambiantly_color);
	// light_coef = scalar_product(params->normal->axis,
	// 		light_ray.ray.dir_vect.axis);
	// if (is_ambianced_only(params, &light_ray, &light_coef, &ambiantly_color))
	// 	return ;
	// calculate_spotlight_effect(&(t_calc_spotlight_effect_params)
	// {params, &cyl->color, params->normal, &spotlighty_color, &light_ray});

	add_color(&spotlighties_color, &ambiantly_color, params->color);
	apply_aces_tonemap(params->color);
}

/**========================================================================
 *                           HANDLE_NORMAL_SYMMETRIZATION
 *========================================================================**/
void	handle_normal_symmetrization(t_get_color_params *params, t_ray_vector
*normal, t_ray *light_ray)
{
	double			light_dot_normal;
	t_cylinder		*cyl;

	cyl = ((t_cylinder *) params->mesh->ref);
	// 	double			view_dot_normal;
	// view_dot_normal = scalar_product(normal->axis, params->ray->dir_vect.axis);
	// if (view_dot_normal > 0.0)
	// 	symmetrize_vector(normal->axis);
	light_dot_normal = scalar_product(normal->axis, light_ray->dir_vect.axis);
	if (light_dot_normal < 0 && cyl->which_t == 2)
		symmetrize_vector(normal->axis);
}

/**========================================================================
 *                           IS_AMBIANCED_ONLY
 *========================================================================**/
static int	is_ambianced_only(t_spotlight *spotlight, t_get_color_params *params,
	t_ray_pack *light_ray, double *light_coef)
{
	t_cylinder		*cyl;

	cyl = ((t_cylinder *) params->mesh->ref);
	if (has_shadow(params->data, params->mesh, light_ray)
		|| *light_coef < 0.0 || are_light_and_cam_in_different_cyl_space
		(params->normal, spotlight, cyl, &params->data->cam))
		return (1);	
	return (0);
}
