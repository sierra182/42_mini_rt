// #include "x_mini_struct.h"
// #include "x_linear_algebra.h"
// #include <math.h>

// void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
// void	color_with_light(t_color *mesh_color,
// 			t_color *light_color, double intensity, t_color *new_color);
// void	add_shading( t_ray *ray, t_ray_vector *normal,
// 			t_color *ambiantly_color, t_color *color);
// int		has_shadow(t_data *data, void *mesh, t_ray *light_ray);
// int		are_light_and_cam_in_different_cyl_space(t_ray_vector *normal,
// 			t_spotlight *light, t_cylinder *cyl, t_cam *cam);
// void	add_self_shadowing(double light_coef, double light_attenuation,
// 			t_color *color);
// void	add_lightening(t_add_lightening_params *params);
// void	limit_to_255(t_color *color);

// /**========================================================================
//  *                           get_cylinder_color_discs_2
//  *========================================================================**/
// int	get_cylinder_color_discs_2(t_get_cylinder_color_discs_params *p)
// {
// 	double			light_attenuat;
// 	double			light_coef;
// 	t_cylinder		*cyl;
// 	t_color			ambiantly_color;
// 	t_color			spotlighty_color;

// 	cyl = ((t_cylinder *) p->params->mesh);
// 	light_coef = scalar_product(p->normal->axis, p->light_ray
// 			->dir_vect.axis);
// 	if (has_shadow(p->params->data, p->params->mesh, p->light_ray)
// 		|| light_coef < 0.0
// 		|| are_light_and_cam_in_different_cyl_space(p->normal, &p
// 			->params->data
// 			->spotlight, cyl, &p->params->data->cam))
// 		return (*p->params->color = ambiantly_color, 0);
// 	add_lightening(&(t_add_lightening_params){p->light_ray, p->normal,
// 		&p->params->data->spotlight, &ambiantly_color, p->params->color,
// 		&light_attenuat, &light_coef});
// 	add_self_shadowing(light_coef, light_attenuat, &spotlighty_color);
// 	add_color(&spotlighty_color, &ambiantly_color, p->params->color);
// 	limit_to_255(p->params->color);
// 	return (0);
// }

// /**========================================================================
//  *                           get_cylinder_color_discs_0
//  *========================================================================**/
// void	get_cylinder_color_discs_0(t_get_color_params *params,
// 		t_ray_vector *normal)
// {
// 	t_cylinder		*cyl;
// 	t_color			ambiantly_color;
// 	t_color			spotlighty_color;

// 	cyl = ((t_cylinder *) params->mesh);
// 	color_with_light(&cyl->color, &params->data->ambiant_light.color,
// 		params->data->ambiant_light.intensity, &ambiantly_color);
// 	color_with_light(&cyl->color, &(t_color){.rgb[0] = 255, .rgb[1] = 255,
// 		.rgb[2] = 255}, params->data->spotlight.intensity, &spotlighty_color);
// 	add_shading(params->ray, normal, &ambiantly_color, &ambiantly_color);
// 	add_shading(params->ray, normal, &spotlighty_color, &spotlighty_color);
// }

// /**========================================================================
//  *                           get_cylinder_color_discs
//  *========================================================================**/
// int	get_cylinder_color_discs(t_get_color_params *params)
// {
// 	t_ray_vector	normal;
// 	t_ray			light_ray;
// 	double			view_dot_normal;
// 	t_cylinder		*cyl;
// 	double			light_dot_normal;

// 	cyl = ((t_cylinder *) params->mesh);
// 	cast_vector_mat_ray(&cyl->axis_vect, &normal);
// 	get_intersect_point(params->ray, params->t, &light_ray.origin_vect);
// 	subtract_vector(params->data->spotlight.origin_vect.axis,
// 		light_ray.origin_vect.axis, light_ray.dir_vect.axis);
// 	view_dot_normal = scalar_product(normal.axis, params->ray->dir_vect.axis);
// 	if (view_dot_normal > 0.0)
// 		symmetrize_vector(normal.axis);
// 	light_dot_normal = scalar_product(normal.axis, light_ray.dir_vect.axis);
// 	if (light_dot_normal < 0 && cyl->which_t == 2)
// 		symmetrize_vector(normal.axis);
// 	get_cylinder_color_discs_0(params, &normal);
// 	return (get_cylinder_color_discs_2(&(t_get_cylinder_color_discs_params)
// 			{params, &normal, &light_ray}));
// }
