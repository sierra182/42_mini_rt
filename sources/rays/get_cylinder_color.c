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

/**========================================================================
 *                           GET_CYLINDER_COLOR_CYL
 *
 * @brief Get the cylinder color cyl object
 * 
 * @param params 
 * @return int 
*========================================================================**/
int	is_in_cyl_diam( t_cylinder *cyl, t_ray_vector *normal, double mesh[])
{
	t_ray_vector	subt_vect;
	t_ray_vector	inter_vect;
	
	t_ray			ray;

	// ray.dir_vect = *normal;
	cast_vector_mat_ray(&cyl->axis_vect, &ray.dir_vect);
	cast_vector_mat_ray(&cyl->origin_vect, &ray.origin_vect);
	subtract_vector(mesh, cyl->origin_vect.axis, subt_vect.axis);
		 normalize_vector(ray.dir_vect.axis);

	//get_intersect_point(&ray, scalar_product(normal->axis, subt_vect.axis), &inter_vect);
	 scale_vector(ray.dir_vect.axis, scalar_product(ray.dir_vect.axis, subt_vect.axis), inter_vect.axis);
	subtract_vector(inter_vect.axis, subt_vect.axis, subt_vect.axis);
	if (get_vector_magnitude(subt_vect.axis) <= cyl->diameter * 0.5)
		return (1);
	else
		return (0);
}

void	print_delay(t_ray_vector *subt_vect, double diam)
{
	static int delay;

	delay = (delay + 1) % 1800;
	if (!delay)
		printf("mag:%f rayon:%f\n", get_vector_magnitude(subt_vect->axis), diam * 0.5 );
}

int	is_cylinder_surface_between2( t_cylinder *cyl, t_ray_vector *normal, double mesh[])
{
	t_ray_vector	subt_vect;
	t_ray_vector	inter_vect;
	
	t_ray			ray;
		

	//ray.dir_vect = cyl->axis_vect;//*normal;
	//symmetrize_vector(ray.dir_vect.axis);
	cast_vector_mat_ray(&cyl->axis_vect, &ray.dir_vect);
	cast_vector_mat_ray(&cyl->origin_vect, &ray.origin_vect);
	subtract_vector(mesh, cyl->origin_vect.axis, subt_vect.axis);
	
	normalize_vector(ray.dir_vect.axis);
	scale_vector(ray.dir_vect.axis,  scalar_product(ray.dir_vect.axis, subt_vect.axis), inter_vect.axis);

	//  get_intersect_point(&ray, scalar_product(normal->axis, subt_vect.axis), &inter_vect);
	
	subtract_vector(inter_vect.axis, subt_vect.axis, subt_vect.axis);	
	//print_delay(&subt_vect, cyl->diameter);	
	
		return ((get_vector_magnitude(subt_vect.axis) >= cyl->diameter * 0.5
	&& cyl->which_t == 2) || ((get_vector_magnitude(subt_vect.axis) <= cyl->diameter * 0.5
	&& cyl->which_t == 1)));
}
int is_in_cyl_height(t_ray_vector *normal, t_cylinder *cyl, double mesh[])
{
	t_ray_vector	subt_vect;

	subtract_vector(mesh, cyl->origin_vect.axis, subt_vect.axis);
	// normalize_vector(subt_vect.axis);
	if (fabs(scalar_product(normal->axis, subt_vect.axis)) < cyl->height * 0.5)	
	{
		 // printf("IN\n");
		return (1);
	}	
	//   printf("OUT\n");
	return (0);
}

int	is_in_cylinder(t_ray_vector *normal, t_cylinder *cyl, double mesh[])
{
	return (is_in_cyl_height(normal, cyl, mesh)
		&& is_in_cyl_diam(cyl, normal, mesh));
}
int	are_light_and_cam_in_different_cyl_space(t_ray_vector *normal, t_spotlight *light, t_cylinder *cyl, t_cam *cam)
{
	if (is_in_cylinder(normal, cyl, light->origin_vect.axis)
		&& is_in_cylinder(normal, cyl, cam->origin_vect.axis))	
	{
	//	printf("same IN\n");	
		return (0);
	}
	if (!is_in_cylinder(normal, cyl, light->origin_vect.axis)
		&& !is_in_cylinder(normal, cyl, cam->origin_vect.axis))	
	{
	//	printf("same OUT\n");	
		return (0);
	}
	//printf("different space\n");	
	return (1);
}
	// if (has_shadow(params->data, cyl, &light_ray) || are_light_and_cam_in_different_cyl_space(&normal, &params->data->spotlight, cyl, &params->data->cam))
	// if (has_shadow(params->data, cyl, &light_ray) || is_in_cyl_diam(cyl, &normal, params->data->spotlight.origin_vect.axis))
	// if (has_shadow(params->data, cyl, &light_ray) || is_cylinder_surface_between2(cyl, &normal, params->data->spotlight.origin_vect.axis))

int	get_cylinder_color_cyl(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;
	double			light_attenuat;
	double			light_coef;
	t_cylinder		*cyl;
	t_ray_vector	intersect_point;
	t_ray_vector	cyl_to_intersect;
	double			proj;
	t_ray_vector	proj_vect;
	t_color			spotlighty_color;

	cyl = (t_cylinder *)params->mesh;
	get_intersect_point(params->ray, params->t, &intersect_point);
	subtract_vector(intersect_point.axis, cyl->origin_vect.axis,
		cyl_to_intersect.axis);
	proj = scalar_product(cyl_to_intersect.axis, cyl->axis_vect.axis);
	scale_vector(cyl->axis_vect.axis, proj, proj_vect.axis);
	subtract_vector(cyl_to_intersect.axis, proj_vect.axis, normal.axis);
	normalize_vector(normal.axis);
	if (((t_cylinder *)params->mesh)->which_t == 2)
		symmetrize_vector(normal.axis);
	light_ray.origin_vect = intersect_point;
	subtract_vector(params->data->spotlight.origin_vect.axis, light_ray
		.origin_vect.axis, light_ray.dir_vect.axis);
	color_with_light(&cyl->color, &params->data->ambiant_light.color, params->data->ambiant_light.intensity, &ambiantly_color);
	color_with_light(&cyl->color, &(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255}, params->data->spotlight.intensity, &spotlighty_color);
	add_shading(params->ray, &normal, &ambiantly_color, &ambiantly_color);
	add_shading(params->ray, &normal, &spotlighty_color, &spotlighty_color);
	t_ray_vector tmp;
	cast_vector_mat_ray(&cyl->axis_vect, &tmp);
	// normalize_vector(normal.axis);
	if (has_shadow(params->data, cyl, &light_ray) || is_cylinder_surface_between2(cyl, &normal, params->data->spotlight.origin_vect.axis)
	|| !is_in_cyl_height(&tmp, cyl, params->data->spotlight.origin_vect.axis))
		return (*params->color = ambiantly_color, 0);
	add_lightening(&(t_add_lightening_params){&light_ray, &normal, &params
		->data->spotlight, &ambiantly_color, params->color,
		&light_attenuat, &light_coef});
	add_self_shadowing(light_coef, light_attenuat, &spotlighty_color);
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	limit_to_255(params->color);
	return (0);
}

/**========================================================================
 *                           GET_CYLINDER_COLOR_DISCS
 * @brief Get the cylinder color discs object
 * 
 * @param params 
 * @return int 
 *========================================================================**/
// void	get_vector_from_distance(t_ray *ray, double t, t_ray_vector *inter_pt)
// {
// 	t_ray_vector	scaled_vect;

// 	scale_vector(ray->dir_vect.axis, t, scaled_vect.axis);
// 	add_vector(ray->origin_vect.axis, scaled_vect.axis, inter_pt->axis);
// }


int	get_cylinder_color_discs(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray			light_ray;
	t_color			ambiantly_color;
	double			light_dot_normal;
	double			view_dot_normal;
	t_color			spotlighty_color;
	double			light_attenuat;
	double			light_coef;
	t_cylinder		*cyl;
	double tmp[3];

	cyl = ((t_cylinder *) params->mesh);
	cast_vector_mat_ray(&cyl->axis_vect, &normal);
	get_intersect_point(params->ray, params->t, &light_ray.origin_vect);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray.origin_vect.axis, light_ray.dir_vect.axis);
	view_dot_normal = scalar_product(normal.axis, params->ray->dir_vect.axis);
	if (view_dot_normal > 0.0)//1e-5)
		symmetrize_vector(normal.axis);
	light_dot_normal = scalar_product(normal.axis, light_ray.dir_vect.axis);
	if (light_dot_normal < 0 && cyl->which_t == 2)
		symmetrize_vector(normal.axis);
	color_with_light(&cyl->color, &params->data->ambiant_light.color, params->data->ambiant_light.intensity, &ambiantly_color);
	color_with_light(&cyl->color, &(t_color){.rgb[0] = 255, .rgb[1] = 255, .rgb[2] = 255}, params->data->spotlight.intensity, &spotlighty_color);
	add_shading(params->ray, &normal, &ambiantly_color, &ambiantly_color);
	add_shading(params->ray, &normal, &spotlighty_color, &spotlighty_color);

	//calculer vecteur egale a spotlight origin vecto- cylinder origin vector
	// on projete le vecteur obtenu sur l'axe du cyl (produit scalaire)
	// on peut ensuite comparer avec h/2

	//
	light_coef = scalar_product(normal.axis, light_ray.dir_vect.axis);
	//is_light_in_cyl_height(&normal, cyl, &params->data->spotlight);
	//is_in_cylinder_diam(cyl, &normal, params->data->spotlight.origin_vect.axis);
	//  || light_coef < 0.0 ||
	if (has_shadow(params->data, params->mesh, &light_ray) ||  light_coef < 0.0 || are_light_and_cam_in_different_cyl_space(&normal, &params->data->spotlight, cyl, &params->data->cam))
	// ( !is_in_cyl_height(&normal, cyl, params->data->spotlight.origin_vect.axis) 
	// && || !is_in_cylinder_diam(cyl, &normal, params->data->spotlight.origin_vect.axis)))//  (!is_cylinder_surface_between(cyl, &params->data->spotlight) && ))
		return (*params->color = ambiantly_color, 0);

	add_lightening(&(t_add_lightening_params){&light_ray, &normal, &params
		->data->spotlight, &ambiantly_color, params->color,
		&light_attenuat, &light_coef});
	add_self_shadowing(light_coef, light_attenuat, &spotlighty_color);
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	limit_to_255(params->color);
	return (0);
}

/**========================================================================
 *                           GET_CYLINDER_COLOR
 * @brief Get the cylinder color object
 * 
 * @param data 
 * @param ray 
 * @param obj 
 * @param color 
 *========================================================================**/
void	get_cylinder_color(t_data *data, t_ray *ray, t_obj *obj,
		t_color *color)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)obj->ref;
	if (cyl->cyl_or_discs == cylinder)
	{
		get_cylinder_color_cyl(&(t_get_color_params)
		{data, ray, obj->t, obj->ref, color});
	}
	if (cyl->cyl_or_discs == discs)
	{
		get_cylinder_color_discs(&(t_get_color_params)
		{data, ray, obj->t, obj->ref, color});
	}
}
