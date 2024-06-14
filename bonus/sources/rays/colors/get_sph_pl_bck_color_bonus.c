#include "get_sph_pl_bck_color_bonus.h"
void	clamp_rgb_0(t_color *color);
#include <math.h>

/**========================================================================
 *                           COMPUTE_SPHERE_NORMAL_AND_LIGHT_RAY
 *========================================================================**/
void	compute_sph_normal_and_light_ray(t_get_color_params *params,
	t_sphere *sphere, t_ray_vector *normal, t_ray_pack *light_ray)
{
	get_intersect_point(params->ray, params->t, &light_ray->ray.origin_vect);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray->ray.origin_vect.axis, light_ray->ray.dir_vect.axis);
	calculate_ray_pack(light_ray);
	subtract_vector(light_ray->ray.origin_vect.axis,
		sphere->origin_vect.axis, normal->axis);
	self_normalize_vector(normal->axis);
	if (sphere->which_t == 2)
		symmetrize_vector(normal->axis);
}

void cartesian_to_spherical(t_ray_vector *point, float *theta, float *phi)
{
	float r;
	
	r = sqrt(point->axis[0]* point->axis[0]+ point->axis[1] * point->axis[1] + point->axis[2] * point->axis[2]);
	*theta = acos(point->axis[2] / r);
	*phi = atan2(point->axis[1], point->axis[0]);
}

int is_checkerboard(t_ray_vector point, float size)
{
	float theta;
	float phi;
	int check_theta;
	int check_phi;

	cartesian_to_spherical(&point, &theta, &phi);

	// Convertir theta et phi en indices de damier
	check_theta = (int)(theta / size) % 2;
	check_phi = (int)(phi / size) % 2;

	// Alterner les couleurs selon les indices
	return (check_theta + check_phi) % 2 == 0;
}

void	checker_board_modif(t_get_color_params *params, t_color *color_altered, t_ray_vector *i_point)
{
	t_sphere		*sphere;

	int i;

	sphere = (t_sphere *) params->mesh->ref;
	if (sphere->checkerboard == 0)
		return ;
	i = 0;
	while (i < 3)
	{
		// printf("color->rgb[%d] = %d\n", i, sphere->color.rgb[i]);
		color_altered->rgb[i] = sphere->color.rgb[i];
		i++;
	}
		// color_altered->rgb[0] -= 50;
		// color_altered->rgb[1] -= 50;
		// color_altered->rgb[2] -= 50;

	// sphere->color.rgb[0] -= 50;
	// sphere->color.rgb[1] -= 50;
	// sphere->color.rgb[2] -= 50;
	if (is_checkerboard(*i_point, 0.05))
	{
		*params->color = *color_altered;
		apply_aces_tonemap(params->color);
		return ;
	}
	params->color->rgb[0] -= 50;
	params->color->rgb[1] -= 50;
	params->color->rgb[2] -= 50;

	clamp_rgb_0(params->color);
}


void calculate_uv(t_ray_vector point, double *u, double *v) {
	double theta;
	double phi;
	
	theta = atan2(point.axis[2], point.axis[0]);
	phi = asin(point.axis[1]);
	*u = 0.5 + theta / (2 * M_PI);
	*v = 0.5 - phi / M_PI;
	printf("u = %f, v = %f\n", *u, *v);
}

void checker_color(double u, double v, int checker_size, int *rgb)
{
	int u_index = (int)(u * checker_size);
	int v_index = (int)(v * checker_size);
	int	is_checker;
	is_checker = (u_index % 2 == v_index % 2);

	
	if (is_checker)
	{
		rgb[0] = 0;
		rgb[1] = 0;
		rgb[2] = 0;
	}
	else
	{
		rgb[0] = 255;
		rgb[1] = 255;
		rgb[2] = 255;
	}
}

void	checker_board_modif_uv(t_get_color_params *params, t_ray_pack light_ray, int size)
{
	double u, v;
	t_sphere		*sphere;

	sphere = (t_sphere *) params->mesh->ref;
	if (sphere->checkerboard == 0)
		return ;
	// self_normalize_vector(light_ray.ray.origin_vect.axis);

	// t_ray_vector i_point;
	// subtract_vector(light_ray.ray.origin_vect.axis, sphere->origin_vect.axis, i_point.axis);

	t_ray_vector local_point;

    local_point.axis[0] = light_ray.ray.origin_vect.axis[0] - sphere->origin_vect.axis[0];
    local_point.axis[1] = light_ray.ray.origin_vect.axis[1] - sphere->origin_vect.axis[1];
    local_point.axis[2] = light_ray.ray.origin_vect.axis[2] - sphere->origin_vect.axis[2];





	self_normalize_vector(local_point.axis);
	calculate_uv(local_point, &u, &v);
	checker_color(u, v, size, params->color->rgb);

}

/**========================================================================
 *                           GET_SPHERE_COLOR
 *========================================================================**/
int	get_sphere_color(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray_pack		light_ray;
	t_color			ambiantly_color;
	t_color			spotlighty_color;
	t_sphere		*sphere;
	t_color 		color_altered;

	sphere = (t_sphere *) params->mesh->ref;
	compute_sph_normal_and_light_ray(params, sphere, &normal, &light_ray);
	calculate_ambiant_effect(params, &sphere->color, &normal,
		&ambiantly_color);
	if (is_sphere_surface_between(params->mesh->ref, &params->data->spotlight)
		|| (has_shadow(params->data, params->mesh, &light_ray)
			&& scalar_product(light_ray.ray.dir_vect.axis, normal.axis) > 0))
	{
		*params->color = ambiantly_color;
		apply_aces_tonemap(params->color);
		return (0);
	}
	calculate_spotlight_effect(&(t_calc_spotlight_effect_params)
	{params, &sphere->color, &normal, &spotlighty_color, &light_ray});
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	// checker_board_modif(params, &color_altered, &light_ray.ray.origin_vect);

	checker_board_modif_uv(params, light_ray, 10);
	

	apply_aces_tonemap(params->color);
	return (0);
}

/**========================================================================
 *                           COMPUTE_PL_NORMAL_AND_LIGHT_RAY
 *========================================================================**/
void	compute_pl_normal_and_light_ray(t_get_color_params *params,
	t_plane *plane, t_ray_vector *normal, t_ray_pack *light_ray)
{
	double	view_dot_normal;

	cast_vector_mat_ray(&plane->norm_vect, normal);
	self_normalize_vector(normal->axis);
	get_intersect_point(params->ray, params->t, &light_ray->ray.origin_vect);
	subtract_vector(params->data->spotlight.origin_vect.axis,
		light_ray->ray.origin_vect.axis, light_ray->ray.dir_vect.axis);
	calculate_ray_pack(light_ray);
	view_dot_normal = scalar_product(normal->axis, params->ray->dir_vect.axis);
	if (view_dot_normal > 0)
		symmetrize_vector(normal->axis);
}


/**========================================================================
 *                           GET_PLANE_COLOR
 *========================================================================**/
int	get_plane_color(t_get_color_params *params)
{
	t_ray_vector	normal;
	t_ray_pack		light_ray;
	t_color			ambiantly_color;
	t_color			spotlighty_color;
	t_plane			*plane;

	plane = ((t_plane *) params->mesh->ref);
	compute_pl_normal_and_light_ray(params, plane, &normal, &light_ray);
	calculate_ambiant_effect(params, &plane->color, &normal, &ambiantly_color);
	if (has_shadow(params->data, params->mesh, &light_ray)
		|| scalar_product(normal.axis, light_ray.ray.dir_vect.axis) < 1e-3)
	{
		*params->color = ambiantly_color;
		apply_aces_tonemap(params->color);
		return (0);
	}
	calculate_spotlight_effect(&(t_calc_spotlight_effect_params)
	{params, &plane->color, &normal, &spotlighty_color, &light_ray});
	add_color(&spotlighty_color, &ambiantly_color, params->color);
	apply_aces_tonemap(params->color);
	return (0);
}

/**========================================================================
 *                           GET_BACKGROUND_COLOR
 *========================================================================**/
int	get_background_color(t_ray *ray, t_data *data)
{
	int		color[2];
	int		rgb[3];
	double	dir;
	t_color	*bg_color;
	double	intensity;

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
