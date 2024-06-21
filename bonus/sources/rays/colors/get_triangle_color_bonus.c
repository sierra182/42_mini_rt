#include "get_triangle_color_bonus.h"

/**========================================================================
 *                           COMPUTE_TR_NORMAL
 *========================================================================**/
void	compute_tr_normal(t_get_color_params *params,
	t_ray_vector *normal, t_ray_pack *light_ray)
{
	t_triangle	*triangle;
	double		scalar_nr;

	triangle = (t_triangle *) params->mesh->ref;
	get_intersect_point(params->ray, params->t, &light_ray->ray.origin_vect);
	cross_product(triangle->e1.axis, triangle->e2.axis, normal->axis);
	self_normalize_vector(normal->axis);
	scalar_nr = scalar_product(normal->axis, params->ray->dir_vect.axis);
	if (scalar_nr > 0)
		symmetrize_vector(normal->axis);
}

/**========================================================================
 *                         ADD_TR_SPOTLIGHTS_EFFECT
 *========================================================================**/
static void	add_tr_spotlights_effect(t_get_color_params *params,
	t_ray_vector *normal, t_color *spotlighties_color, t_ray_pack *light_ray)
{
	t_color		spotlighty_color;
	t_triangle	*triangle;
	int			i;

	triangle = (t_triangle *) params->mesh->ref;
	*spotlighties_color = (t_color){.rgb[0] = 0, .rgb[1] = 0, .rgb[2] = 0};
	i = -1;
	while (++i < params->data->sl_nbr)
	{
		compute_light_ray(&params->data->spotlights[i], light_ray);
		if (has_shadow(params->data, params->mesh, light_ray)
			|| scalar_product(normal->axis, light_ray->ray.dir_vect.axis)
			< 1e-3)
			continue ;
		calculate_spotlight_effect(&(t_calc_spotlight_effect_params)
		{params, &triangle->color, normal, &spotlighty_color, light_ray,
			&params->data->spotlights[i]});
		add_color(spotlighties_color, &spotlighty_color, spotlighties_color);
	}
}

/**========================================================================
 *                           GET_TRIANGLE_COLOR
 *========================================================================**/
void	get_triangle_color(t_get_color_params *params)
{	
	// t_ray_pack		light_ray;
	t_color			ambiantly_color;
	t_color			spotlighties_color;
	t_triangle		*triangle;

	triangle = (t_triangle *) params->mesh->ref;
	// compute_tr_normal(params, &normal, &light_ray);
	calculate_ambiant_effect(params, &triangle->color, params->normal,
		&ambiantly_color);
	add_tr_spotlights_effect(params, params->normal, &spotlighties_color,
		params->light_ray);
	add_color(&spotlighties_color, &ambiantly_color, params->color);
	// apply_aces_tonemap(params->color);
}
