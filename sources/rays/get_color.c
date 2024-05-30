# include "x_mini_struct.h"
# include "x_linear_algebra.h"
# include "x_color_effect.h"

int		has_shadow(t_data *data, t_obj *mesh, t_ray *light_ray);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
int		is_sphere_surface_between(t_sphere *sphere, t_spotlight *spotlight);

void	calculate_spotlight_effect(t_sphere *sphere, t_ray_vector *normal,
	t_color *spotlighty_color )
{
	color_with_light(&sphere->color,
		&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255},
			params->data->spotlight.intensity, spotlighty_color);
	add_shading(params->ray, normal, spotlighty_color, spotlighty_color);
	add_lightening(&(t_add_lightening_params){&light_ray, normal,
		&params->data->spotlight, spotlighty_color,  spotlighty_color,
		&light_attenuat, &light_coef});
	add_self_shadowing(light_coef, light_attenuat, spotlighty_color);
}

void	calculate_ambiant_effect(t_get_color_params *params, t_sphere *sphere,
	t_ray_vector *normal, t_color *ambiantly_color)
{
	color_with_light(&sphere->color,
		&params->data->ambiant_light.color,
			params->data->ambiant_light.intensity, ambiantly_color);
	add_shading(params->ray, normal, ambiantly_color, ambiantly_color);
}

void	compute_normal_and_light_ray(t_get_color_params *params,
	t_sphere *sphere,  t_ray_vector *normal, t_ray *light_ray)
{
	get_intersect_point(params->ray, params->t, &light_ray->origin_vect);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray->origin_vect.axis, light_ray->dir_vect.axis);
	subtract_vector(light_ray->origin_vect.axis,
		sphere->origin_vect.axis, normal->axis);
	normalize_vector(normal->axis);
	if (sphere->which_t == 2)
		symmetrize_vector(normal->axis);
}
//! change proto
int	get_sphere_color(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;
	t_color			spotlighty_color;
	double			light_attenuat;
	double			light_coef;	
	t_sphere 		*sphere;
	
	sphere = (t_sphere *) params->mesh->ref;
	compute_normal_and_light_ray(params, sphere, &normal, &light_ray);
	calculate_ambiant_effect(params, sphere, &normal, &ambiantly_color);
	if (is_sphere_surface_between(params->mesh->ref, &params->data->spotlight)
		|| has_shadow(params->data, params->mesh, &light_ray))
		return (*params->color = ambiantly_color, 0);
	// color_with_light(&((t_sphere *) params->mesh->ref)->color,
	// 	&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255}, params->data->spotlight.intensity, &spotlighty_color);
	// add_shading(params->ray, &normal, &spotlighty_color, &spotlighty_color);

	// add_lightening(&(t_add_lightening_params){&light_ray, &normal,
	// 	&params->data->spotlight, &spotlighty_color,  &spotlighty_color,
	// 	&light_attenuat, &light_coef});
	// add_self_shadowing(light_coef, light_attenuat, &spotlighty_color);
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	limit_to_255(params->color);
	return (0);
} 


void	get_plane_color(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;
	double view_dot_normal;
	t_color			spotlighty_color;
	t_plane		*plane;
	double			light_attenuat;
	double			light_coef;	 
	plane = ((t_plane *) params->mesh->ref);

	cast_vector_mat_ray(&plane->norm_vect, &normal);
	get_intersect_point(params->ray, params->t, &light_ray.origin_vect);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	normalize_vector(params->ray->dir_vect.axis);
	view_dot_normal = scalar_product(normal.axis, params->ray->dir_vect.axis);
	if (view_dot_normal > 0)
		symmetrize_vector(normal.axis);
	color_with_light(&plane->color,
		&params->data->ambiant_light.color, params->data->ambiant_light.intensity, &ambiantly_color);
	color_with_light(&plane->color,
		&(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255 }, params->data->spotlight.intensity, &spotlighty_color);
	add_shading(params->ray, &normal, &ambiantly_color, &ambiantly_color);
	add_shading(params->ray, &normal, &spotlighty_color, &spotlighty_color);
	light_coef = scalar_product(normal.axis, light_ray.dir_vect.axis);
	if (has_shadow(params->data, params->mesh, &light_ray) || light_coef < 1e-3)
	{
		*params->color = ambiantly_color;
		return ;
	}
	add_lightening(&(t_add_lightening_params){&light_ray, &normal,
		&params->data->spotlight, &spotlighty_color,  &spotlighty_color,
		&light_attenuat, &light_coef});
	add_self_shadowing(light_coef, light_attenuat, &spotlighty_color);
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	limit_to_255(params->color);
}

int	get_background_color(t_ray *ray, t_data *data)
{
	int		color[2];
	int		rgb[3];
	double	dir;
	t_color *bg_color;
	double 	intensity;

	intensity = data->ambiant_light.intensity;
	bg_color = (t_color *)&data->ambiant_light.color;
	dir = (ray->dir_vect.axis[1] + 1.0) * 0.5;
	color[0] = get_color(intensity * 255, intensity * 255, intensity * 255);
	color[1] = get_color(bg_color->rgb[0] * intensity, bg_color->rgb[1]
		* intensity, bg_color->rgb[2] * intensity);
	rgb[0] = (int)((1.0 - dir) * ((color[1] >> 16) & 0xFF) + dir
		* ((color[0] >> 16) & 0xFF));
	rgb[1] = (int)((1.0 - dir) * ((color[1] >> 8) & 0xFF) + dir
		* ((color[0] >> 8) & 0xFF));
	rgb[2] = (int)((1.0 - dir) * (color[1] & 0xFF) + dir * (color[0] & 0xFF));	
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
