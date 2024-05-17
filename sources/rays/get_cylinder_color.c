/* IDEA IS AS FOLLOWS:
		at intersection, determine wether is_plane or is_cyl
		=> redirect to corresponding get_color func
*/

void	get_cylinder_color(t_get_color_params *params)
{
	ray_interecting_cyl_or_discs();
	// if intersect_cyl
		// call get_cylinder_color_cyl
	// else if intersect_discs
		// call get_cylinder_color_discs
}

int	get_cylinder_color_cyl(t_get_color_params *params)
{
	//t_ray_vector	normal;
	//t_ray			light_ray;
	//t_color			ambiantly_color;
	//double			light_attenuat;
	//double			light_coef;	

	//get_intersect_point(params->ray, params->t, &light_ray.origin_vect);
	//subtract_vector(light_ray.origin_vect.axis,
	//	((t_sphere *) params->mesh)->origin_vect.axis, normal.axis);
	//normalize_vector(normal.axis);
	//subtract_vector(params->data->spotlight.origin_vect.axis,
	//	light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	//color_with_ambiant_light(&((t_sphere *) params->mesh)->color,
	//	&params->data->ambiant_light, &ambiantly_color);
	//if (((t_sphere *) params->mesh)->which_t == 2)
	//	symmetrize_vector(normal.axis);
	//add_initial_shading(params->ray, &normal, &ambiantly_color, params->color);
	//if (has_shadow(params->data, (t_sphere *) params->mesh, &light_ray))
	//	return (*params->color = ambiantly_color, 0);
	//add_shading(&(t_add_shading_params){&light_ray, &normal,
	//	&params->data->spotlight, &ambiantly_color, params->color,
	//	&light_attenuat, &light_coef});
	//add_self_shadowing(light_coef, light_attenuat, params->color);
	//return (0);
}

void	get_cylinder_color_discs(t_get_color_params *params)
{
	//t_ray_vector	normal;
	//t_ray			light_ray;
	//t_color			ambiantly_color;

	//cast_vector_mat_ray(&((t_plane *) params->mesh)->norm_vect, &normal);
	//get_intersect_point(params->ray, params->t, &light_ray.origin_vect);
	//subtract_vector(params->data->spotlight.origin_vect.axis,
	//	light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	//color_with_ambiant_light(&((t_plane *) params->mesh)->color,
	//	&params->data->ambiant_light, &ambiantly_color);
	//if (has_shadow(params->data, params->mesh, &light_ray))
	//{
	//	*params->color = ambiantly_color;
	//	return ;
	//}
	//add_shading(&(t_add_shading_params){&light_ray, &normal,
	//	&params->data->spotlight, &ambiantly_color, params->color,
	//	&(double){0.0}, &(double){0.0}});
}