#include "x_mini_struct.h"
#include "x_linear_algebra.h"
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
void	color_with_ambiant_light(t_color *mesh_color,
	t_ambiant_light *ambiant_light, t_color *new_color);
int	has_shadow(t_data *data, void *mesh, t_ray *light_ray);
void	add_shading(t_add_shading_params *params);

void	get_plane_color(t_get_color_params *params);
void	add_initial_shading( t_ray *ray, t_ray_vector *normal,
	t_color *ambiantly_color, t_color *color);
void	add_self_shadowing(double light_coef, double light_attenuation,
	t_color *color);

/*
typedef	struct s_obj_intersect
{
	double			t;
	enum e_obj_type	type;
	void			*ref;
}	t_obj;



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

/*
typedef struct s_get_color_params
{
	t_data	*data;
	t_ray	*ray;
	double	t;
	void	*mesh;
	t_color *color;
}	t_get_color_params;
*/

/**========================================================================
 *                           get_cylinder_color_cyl
 *! which_t calculation to be added! 
 *========================================================================**/
int	get_cylinder_color_cyl(t_get_color_params *params)
{

	//todo : change normal calculation

	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;
	double			light_attenuat;
	double			light_coef;	
	t_ray	proj_origin;

	light_ray.origin_vect.axis[0] = ((t_cylinder *) params->mesh)->intersec_point.axis[0];
	light_ray.origin_vect.axis[1] = ((t_cylinder *) params->mesh)->intersec_point.axis[1];
	light_ray.origin_vect.axis[2] = ((t_cylinder *) params->mesh)->intersec_point.axis[2];
	cast_vector_mat_ray(&((t_cylinder *) params->mesh)->axis_vect, &proj_origin.dir_vect);
	get_intersect_point(&proj_origin, ((t_cylinder *) params->mesh)->proj, &((t_cylinder *) params->mesh)->origin_proj);
	subtract_vector(light_ray.origin_vect.axis,
		((t_cylinder *) params->mesh)->origin_proj.axis, normal.axis);
	normalize_vector(normal.axis);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	color_with_ambiant_light(&((t_cylinder *) params->mesh)->color,
		&params->data->ambiant_light, &ambiantly_color);
	if (((t_cylinder *) params->mesh)->which_t == 2)
		symmetrize_vector(normal.axis);
	//add_initial_shading(params->ray, &normal, &ambiantly_color, params->color);
	//if (has_shadow(params->data, (t_cylinder *) params->mesh, &light_ray))
	//	return (*params->color = ambiantly_color, 0);
	//add_shading(&(t_add_shading_params){&light_ray, &normal,
	//	&params->data->spotlight, &ambiantly_color, params->color,
	//	&light_attenuat, &light_coef});
	//add_self_shadowing(light_coef, light_attenuat, params->color);
	return (42);
}

void	get_cylinder_color_discs(t_get_color_params *params)
{


	//printf("intersect discs\n");

	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;

	cast_vector_mat_ray(&((t_cylinder *) params->mesh)->axis_vect, &normal);
	get_intersect_point(params->ray, params->t, &light_ray.origin_vect);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	color_with_ambiant_light(&((t_cylinder *) params->mesh)->color,
		&params->data->ambiant_light, &ambiantly_color);
	if (has_shadow(params->data, params->mesh, &light_ray))
	{
		*params->color = ambiantly_color;
		return ;
	}
	add_shading(&(t_add_shading_params){&light_ray, &normal,
		&params->data->spotlight, &ambiantly_color, params->color,
		&(double){0.0}, &(double){0.0}});
}

void	get_cylinder_color(t_data *data, t_ray *ray, t_obj *obj, t_color	*color)
{
	t_cylinder *cyl = (t_cylinder *)obj->ref;
	//printf("%f, %f, %f\n", cyl->intersec_point.axis[0], cyl->intersec_point.axis[1], cyl->intersec_point.axis[2]);
	
	if (cyl->cyl_or_discs == cylinder)
	{
		color->rgb[0] = 255;
		color->rgb[1] = 0;
		color->rgb[2] = 0;
		//get_cylinder_color_cyl(&(t_get_color_params) {data, ray, obj->t, obj->ref, color});
	}
	if (cyl->cyl_or_discs == discs)
	{
		color->rgb[0] = 0;
		color->rgb[1] = 255;
		color->rgb[2] = 0;
		
		//symmetrize_vector(cyl->axis_vect.axis);
		//get_cylinder_color_discs(&(t_get_color_params) {data, ray, obj->t, obj->ref, color});
	}
}