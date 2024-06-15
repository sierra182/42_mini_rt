#include "get_cylinder_color_bonus.h"

/**========================================================================
 *                           GET_CYLINDER_COLOR
 *========================================================================**/
void	get_cylinder_color(t_data *data, t_ray *ray, t_obj *obj,
		t_color *color)
{
	t_ray_vector	normal;
	t_cylinder		*cyl;

	cyl = (t_cylinder *)obj->ref;
	if (cyl->cyl_or_discs == cylinder)
	{
		get_cylinder_color_cyl(&(t_get_color_params)
		{data, ray, obj->t, obj, color, &normal});
	}
	if (cyl->cyl_or_discs == discs)
	{
		get_cylinder_color_discs(&(t_get_color_params)
		{data, ray, obj->t, obj, color, &normal});
	}
}
int	calculate_spotlight_effect3(t_spotlight *spotlight, t_calc_spotlight_effect_params *params);

void	compute_light_ray(t_spotlight *spotlight, t_get_color_params *params,
	t_ray_pack *light_ray);

void	add_cyl_spotlights_effect(t_get_color_params *params,
	t_ray_vector *normal, t_color *spotlighties_color, t_color *mesh_color, t_ray_pack	*light_ray)
{	
	t_color		spotlighty_color;
	int			i;
	
	*spotlighties_color = (t_color){.rgb[0] = 0, .rgb[1] = 0, .rgb[2] = 0};
	i = -1;
	while (++i < params->data->sl_nbr)
	{
		compute_light_ray(&params->data->spotlights[i], params,
			light_ray);	
		if (is_ambianced_only(&params->data->spotlights[i], params, light_ray))
	 		continue ;
		calculate_spotlight_effect3(&params->data->spotlights[i],
			&(t_calc_spotlight_effect_params)
		{params, mesh_color, normal, &spotlighty_color, light_ray});
		add_color(spotlighties_color, &spotlighty_color, spotlighties_color);
	}
}

/**========================================================================
 *                           GET_CYLINDER_COLOR_CYL
 *========================================================================**/
void	get_cylinder_color_cyl(t_get_color_params *params)
{
	t_ray_pack		light_ray;
	t_color			ambiantly_color;
	t_color			spotlighties_color;
	t_cylinder		*cyl;	

	cyl = (t_cylinder *)params->mesh->ref;
	handle_projection(params, params->normal, &light_ray.ray);	
	// subtract_vector(params->data->spotlight.origin_vect.axis, light_ray //!big pb
	// 	.ray.origin_vect.axis, light_ray.ray.dir_vect.axis);
	// calculate_ray_pack(&light_ray);
	calculate_ambiant_effect(params, &cyl->color, params->normal,
		&ambiantly_color);
	add_cyl_spotlights_effect(params, params->normal, &spotlighties_color,
		&cyl->color, &light_ray);
	add_color(&spotlighties_color, &ambiantly_color, params->color);
	apply_aces_tonemap(params->color);
}

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
	self_normalize_vector(normal->axis);
	if (cyl->which_t == 2)
		symmetrize_vector(normal->axis);
	light_ray->origin_vect = intersect_point;
}

/**========================================================================
 *                           IS_AMBIANCED_ONLY
 *========================================================================**/
static int	is_ambianced_only(t_spotlight *spotlight, t_get_color_params *params, t_ray_pack *light_ray)
{
	t_cylinder		*cyl;
	t_ray_vector	tmp;

	cyl = (t_cylinder *)params->mesh->ref;

	cast_vector_mat_ray(&cyl->axis_vect, &tmp);
	self_normalize_vector(tmp.axis);
	if (has_shadow(params->data, params->mesh, light_ray)
		|| is_cylinder_surface_between (cyl, spotlight->origin_vect.axis) || (!is_in_cyl_height(&tmp, cyl,
				spotlight->origin_vect.axis)
			&& (cyl->which_t == 2)))
		return (1);	
	return (0);
}
