#include "x_mini_struct.h"
#include "x_linear_algebra.h"
#include <math.h>
#include <stdlib.h>

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
int		is_cylinder_surface_between(t_cylinder *cyl, t_spotlight *spotlight);
int		is_in_cyl_height(t_ray_vector *normal, t_cylinder *cyl, double mesh[]);
int		are_light_and_cam_in_different_cyl_space(t_ray_vector *normal,
			t_spotlight *light, t_cylinder *cyl, t_cam *cam);
int		cylinder_surface_intersection( t_cylinder *cyl,
			t_ray_vector *normal, double mesh[]);
int		get_cylinder_color_discs(t_get_color_params *params);

/**========================================================================
 *                           get_cyl_col_cyl_2
 *========================================================================**/
int	get_cyl_col_cyl_2(t_get_cyl_col_cyl_2_params *p)
{
	t_ray_vector	tmp;
	t_cylinder		*cyl;
	double			light_attenuat;
	double			light_coef;

	cyl = (t_cylinder *)p->params->mesh;
	add_shading(p->params->ray, p->normal, p->ambiantly_color,
		p->ambiantly_color);
	add_shading(p->params->ray, p->normal, p->spotlighty_color,
		p->spotlighty_color);
	cast_vector_mat_ray(&cyl->axis_vect, &tmp);
	if (has_shadow(p->params->data, cyl, p->light_ray)
		|| cylinder_surface_intersection(cyl, p->normal, p->params->data
			->spotlight.origin_vect.axis)
		|| (!is_in_cyl_height(&tmp, cyl, p->params->data->spotlight.origin_vect
				.axis) && cyl->which_t == 2))
		return (*p->params->color = *p->ambiantly_color, 0);
	add_lightening(&(t_add_lightening_params){p->light_ray, p->normal,
		&p->params->data->spotlight, p->ambiantly_color, p->params->color,
		&light_attenuat, &light_coef});
	add_self_shadowing(light_coef, light_attenuat, p->spotlighty_color);
	add_color(p->spotlighty_color, p->ambiantly_color, p->params->color);
	limit_to_255(p->params->color);
}

/**========================================================================
 *                        get_cyl_col_cyl_0
 *========================================================================**/
void	get_cyl_col_cyl_0(t_get_cyl_col_cyl_0_params *p)
{
	t_cylinder		*cyl;
	t_ray_vector	intersect_point;
	t_ray_vector	cyl_to_intersect;
	double			proj;
	t_ray_vector	proj_vect;

	cyl = (t_cylinder *)p->params->mesh;
	get_intersect_point(p->params->ray, p->params->t, &intersect_point);
	subtract_vector(intersect_point.axis, cyl->origin_vect.axis,
		cyl_to_intersect.axis);
	proj = scalar_product(cyl_to_intersect.axis, cyl->axis_vect.axis);
	scale_vector(cyl->axis_vect.axis, proj, proj_vect.axis);
	subtract_vector(cyl_to_intersect.axis, proj_vect.axis, p->normal->axis);
	normalize_vector(p->normal->axis);
}

/**========================================================================
 *                           get_cylinder_color_cyl
 *========================================================================**/
int	get_cylinder_color_cyl(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;
	t_cylinder		*cyl;
	t_color			spotlighty_color;

	cyl = (t_cylinder *)params->mesh;
	get_cyl_col_cyl_0(&(t_get_cyl_col_cyl_0_params){params, &normal,
		&light_ray, &ambiantly_color, &spotlighty_color});
	if (cyl->which_t == 2)
		symmetrize_vector(normal.axis);
	subtract_vector(params->data->spotlight.origin_vect.axis, light_ray
		.origin_vect.axis, light_ray.dir_vect.axis);
	color_with_light(&cyl->color, &params->data->ambiant_light.color,
		params->data->ambiant_light.intensity, &ambiantly_color);
	color_with_light(&cyl->color, &(t_color){.rgb[0] = 255, .rgb[1] = 255,
		.rgb[2] = 255}, params->data->spotlight.intensity, &spotlighty_color);
	return (get_cyl_col_cyl_2(&(t_get_cyl_col_cyl_2_params){params, &normal,
			&light_ray, &ambiantly_color, &spotlighty_color}));
}

/**========================================================================
 *                           get_cylinder_color
 *========================================================================**/
void	get_cylinder_color(t_data *data, t_ray *ray, t_obj *obj,
		t_color *color)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)obj->ref;
	if (cyl->cyl_or_discs == cylinder)
		get_cylinder_color_cyl(&(t_get_color_params)
		{data, ray, obj->t, obj->ref, color});
	if (cyl->cyl_or_discs == discs)
		get_cylinder_color_discs(&(t_get_color_params)
		{data, ray, obj->t, obj->ref, color});
}
