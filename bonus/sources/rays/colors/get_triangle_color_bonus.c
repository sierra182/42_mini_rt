# include "se_mini_struct_bonus.h"

/**========================================================================
 *                           GET_TRIANGLE_COLOR
 *========================================================================**/
void	get_triangle_color(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray_pack		light_ray;
	t_color			ambiantly_color;
	t_color			spotlighties_color;
	t_sphere		*sphere;

	sphere = (t_sphere *) params->mesh->ref;
	compute_sph_normal(params, &normal, &light_ray);
	calculate_ambiant_effect(params, &sphere->color, &normal,
		&ambiantly_color);
	add_sph_spotlights_effect(params, &normal, &spotlighties_color,
		&light_ray);
	add_color(&spotlighties_color, &ambiantly_color, params->color);
	apply_aces_tonemap(params->color);
	return (0);
}