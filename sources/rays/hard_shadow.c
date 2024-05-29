# include "x_mini_struct.h"
# include "x_linear_algebra.h"

int		is_same_plane_space(t_plane *a, t_plane *b);
int		is_same_sphere_space(t_sphere *a, t_sphere *b);
int		is_same_cylinder_space(t_cylinder *a, t_cylinder *b);
void	get_local_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
double	is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder,
			t_ray_vector *i);
double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
int	has_sphere_shadow(t_data *data, void *mesh, t_ray *n_light_ray)
{
	int				i;
	double			t;
	long double		mesh_mag;
	long double		light_mag;
	t_ray_vector	intersect_pt;
		
	t_sphere sphere = *(t_sphere *)mesh;
	t_ray tmp =  *n_light_ray;
	t_ray *light_ray = &tmp;
	normalize_vector(light_ray->dir_vect.axis);
	double int_t = is_intersect_sphere(light_ray, &sphere, NULL);
	 // int_t = ((t_sphere *)mesh)->t2;
	// printf("int t: %f\n", int_t);
	// printf("which t: %d\n", sphere.which_t);
	// printf("t2: %f\n", sphere.t2);
	// printf("t1: %f\n\n", sphere.t1);
	i = -1;
	while (++i < data->sp_nbr)
	{
	
		if (mesh && (void *) &data->spheres[i] != mesh && !is_same_sphere_space(&data->spheres[i], mesh))
		{
			t = is_intersect_sphere(light_ray, &data->spheres[i], NULL);
			 if( (t && !int_t)||( t && int_t && int_t < data->spheres[i].t2))
			// if (t && sphere.which_t == 0 || t &&  sphere.which_t == 2 && int_t < data->spheres[i].t2 )

			{
				get_local_intersect_point(light_ray, t, &intersect_pt);
				light_mag = get_vector_magnitude(n_light_ray->dir_vect.axis);
				mesh_mag = get_vector_magnitude(intersect_pt.axis);
				if (mesh_mag - 1e-5 < light_mag)
					return (1);
			}
		}
		

	}
	return (0);
}

int	has_cylinder_shadow(t_data *data, void *mesh, t_ray *n_light_ray)
{
	int				i;
	double			t;
	long double		mesh_mag;
	long double		light_mag;
	t_ray_vector	intersect_pt;

	t_cylinder cylinder = *(t_cylinder *)mesh;
	t_ray tmp =  *n_light_ray;
	t_ray *light_ray = &tmp;
	normalize_vector(light_ray->dir_vect.axis);
	double int_t = is_intersect_cylinder(light_ray, &cylinder, NULL);
	i = -1;
	while (++i < data->cy_nbr)
	{
		if (mesh && (void *) &data->cylinders[i] != mesh && !is_same_cylinder_space(&data->cylinders[i], mesh))
		{
			t = is_intersect_cylinder(light_ray, &data->cylinders[i], NULL);
			// if (t)
						// if( (t > 1e-3 && int_t < 1e-3)||( t > 1e-3 && int_t > 1e-3 && int_t +.1 < data->spheres[i].t2))

			if( (t && int_t < 1e-3)||( t && int_t && int_t < data->spheres[i].t2))
			{
				get_local_intersect_point(light_ray, t, &intersect_pt);
				light_mag = get_vector_magnitude(n_light_ray->dir_vect.axis);
				mesh_mag = get_vector_magnitude(intersect_pt.axis);
				if (mesh_mag - 1e-5 < light_mag)
					return (1);
			}
		}
	}
	return (0);
}

int	has_plane_shadow(t_data *data, void *mesh, t_ray *light_ray)
{
	int				i;
	double			t;
	long double		mesh_mag;
	long double		light_mag;
	t_ray_vector	intersect_pt;

	i = -1;
	while (++i < data->pl_nbr)
	{
		if (mesh && (void *) &data->planes[i] != mesh && !is_same_plane_space(&data->planes[i], mesh))
		{
			t = is_intersect_plane(light_ray, &data->planes[i], NULL);
			if (t)
			{
				get_local_intersect_point(light_ray, t, &intersect_pt);
				light_mag = get_vector_magnitude(light_ray->dir_vect.axis);
				mesh_mag = get_vector_magnitude(intersect_pt.axis);
				if (mesh_mag - 1e-5 < light_mag)
					return (1);
			}
		}
	}
	return (0);
}

int	has_shadow(t_data *data, void *mesh, t_ray *light_ray)
{
	if (has_sphere_shadow(data, mesh, light_ray))
		return (1);
	if (has_cylinder_shadow(data, mesh, light_ray))
		return (1);
	if (has_plane_shadow(data, mesh, light_ray))
		return (1);
	return (0);
}