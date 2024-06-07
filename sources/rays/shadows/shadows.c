#include "se_mini_struct.h"
#include "x_linear_algebra.h"

void	get_local_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
double	is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder,
			t_ray_vector *i);
double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
int		is_in_cylinder(t_ray_vector *normal, t_cylinder *cyl, double mesh[]);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);

int	has_sphere_shadow(t_data *data, t_obj *mesh, t_ray *light_rays[])
{
	int				i;
	double			t;
	double			mesh_mag;
	double			light_mag;
	t_ray_vector	inter_pt;

	i = -1;
	while (++i < data->sp_nbr)
	{
		if (mesh->ref && (void *) &data->spheres[i] != mesh->ref)
		{
			t = is_intersect_sphere(light_rays[1], &data->spheres[i], NULL);
			if (t)
			{
				get_local_intersect_point(light_rays[1], t, &inter_pt);
				mesh_mag = get_vector_magnitude(inter_pt.axis);
				light_mag = get_vector_magnitude(light_rays[0]->dir_vect.axis);
				if (mesh_mag - 1e-5 < light_mag)
					return (1);
			}
		}
	}
	return (0);
}

int	has_cylinder_shadow(t_data *data, t_obj *mesh, t_ray *light_rays[])
{
	int				i;
	double			t;
	double			mesh_mag;
	double			light_mag;
	t_ray_vector	inter_pt;

	i = -1;
	while (++i < data->cy_nbr)
	{
		if (mesh->ref && (void *) & data->cylinders[i] != mesh->ref)
		{
			t = is_intersect_cylinder(light_rays[1], &data->cylinders[i],
					NULL);
			if (t)
			{
				get_local_intersect_point(light_rays[1], t, &inter_pt);
				mesh_mag = get_vector_magnitude(inter_pt.axis);
				light_mag = get_vector_magnitude(light_rays[0]->dir_vect.axis);
				if (mesh_mag - 1e-5 < light_mag)
					return (1);
			}
		}
	}
	return (0);
}

int	has_plane_shadow(t_data *data, t_obj *mesh, t_ray *light_rays[])
{
	int				i;
	double			t;
	double			mesh_mag;
	double			light_mag;
	t_ray_vector	inter_pt;

	i = -1;
	while (++i < data->pl_nbr)
	{
		if (mesh->ref && (void *) &data->planes[i] != mesh->ref)
		{
			t = is_intersect_plane(light_rays[1], &data->planes[i], NULL);
			if (t)
			{
				get_local_intersect_point(light_rays[1], t, &inter_pt);
				light_mag = get_vector_magnitude(light_rays[0]->dir_vect.axis);
				mesh_mag = get_vector_magnitude(inter_pt.axis);
				if (mesh_mag - 1e-5 < light_mag)
					return (1);
			}
		}
	}
	return (0);
}

int	has_shadow(t_data *data, t_ray_vector *normal, t_obj *mesh,
	t_ray *light_ray)
{
	t_ray	light_ray_norm;
	t_ray	light_ray_cpy;

	light_ray_cpy = *light_ray;
	light_ray_norm = *light_ray;
	normalize_vector(light_ray_norm.dir_vect.axis);
	if (has_sphere_shadow(data, mesh,
			(t_ray *[]){&light_ray_cpy, &light_ray_norm})
		|| has_cylinder_shadow(data, mesh,
			(t_ray *[]){&light_ray_cpy, &light_ray_norm})
		|| has_plane_shadow(data, mesh,
			(t_ray *[]){&light_ray_cpy, &light_ray_norm}))
		return (1);
	return (0);
}
