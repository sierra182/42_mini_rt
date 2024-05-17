#include "x_mini_struct.h"

/*
typedef	struct s_obj_intersect
{
	double			t;
	enum e_obj_type	type;
	void			*ref;
}	t_obj;

typedef struct s_get_color_params
{
	t_data	*data;
	t_ray	*ray;
	double	t;
	void	*mesh;
	t_color *color;
}	t_get_color_params;

typedef struct s_add_shading_params
{
	t_ray 			*light_ray;
	t_ray_vector	*normal;
	t_spotlight		*spotlight;
	t_color			*ambiently_color;
	t_color			*color;
	double			*light_attenuat;
	double 			*light_coef;
}	t_add_shading_params;
*/



/* IDEA IS AS FOLLOWS:
		at intersection, determine wether is_plane or is_cyl
		=> redirect to corresponding get_color func
*/



void	get_cylinder_color_cyl()
{

	printf("intersect cylinder\n");

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
}

void	get_cylinder_color_discs()
{
	printf("intersect discs\n");

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

void	get_cylinder_color(t_obj *obj)
{
	t_cylinder *cyl = (t_cylinder *)obj->ref;
	if (cyl->cyl_or_discs == cylinder)
	{
		get_cylinder_color_cyl();

	}
	else if (cyl->cyl_or_discs == discs)
	{
		get_cylinder_color_discs();

	}
}