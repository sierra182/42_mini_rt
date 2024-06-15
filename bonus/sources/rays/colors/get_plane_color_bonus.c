#include "get_plane_color_bonus.h"
void	calculate_spotlight_effect(t_spotlight *spotlight, t_calc_spotlight_effect_params *params);
/**========================================================================
 *                           COMPUTE_PL_NORMAL
 *========================================================================**/
static void	compute_pl_normal(t_get_color_params *params,
	t_plane *plane, t_ray_vector *normal, t_ray_pack *light_ray)
{
	double	scalar_nr;

	get_intersect_point(params->ray, params->t, &light_ray->ray.origin_vect);
	cast_vector_mat_ray(&plane->norm_vect, normal);
	self_normalize_vector(normal->axis);
	scalar_nr = scalar_product(normal->axis, params->ray->dir_vect.axis);
	if (scalar_nr > 0)
		symmetrize_vector(normal->axis);
}

/**========================================================================
 *                         ADD_PL_SPOTLIGHTS_EFFECT
 *========================================================================**/
static void	add_pl_spotlights_effect(t_get_color_params *params,
	t_ray_vector *normal, t_color *spotlighties_color, t_color *mesh_color, t_ray_pack	*light_ray)
{
	t_color	spotlighty_color;
	int		i;

	*spotlighties_color = (t_color){.rgb[0] = 0, .rgb[1] = 0, .rgb[2] = 0};
	i = -1;
	while (++i < params->data->sl_nbr)
	{
		compute_light_ray(&params->data->spotlights[i], params,
			light_ray);
		if (has_shadow(params->data, params->mesh, light_ray)
			|| scalar_product(normal->axis, light_ray->ray.dir_vect.axis)
			< 1e-3)
			continue ;
		calculate_spotlight_effect(&params->data->spotlights[i],
			&(t_calc_spotlight_effect_params)
		{params, mesh_color, normal, &spotlighty_color, light_ray});
		add_color(spotlighties_color, &spotlighty_color, spotlighties_color);
	}
}

/**========================================================================
 *                           GET_PLANE_COLOR
 *========================================================================**/
void	get_plane_color(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray_pack		light_ray;
	t_color			ambiantly_color;	
	t_color			spotlighties_color;
	t_plane			*plane;

	plane = (t_plane *) params->mesh->ref;
	compute_pl_normal(params, plane, &normal, &light_ray);
	calculate_ambiant_effect(params, &plane->color, &normal, &ambiantly_color);
	add_pl_spotlights_effect(params, &normal, &spotlighties_color,
		&plane->color, &light_ray);
	add_color(&spotlighties_color, &ambiantly_color, params->color);
	apply_aces_tonemap(params->color);
}
