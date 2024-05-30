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

int	has_sphere_shadow(t_data *data, t_obj *mesh, t_ray *light_rays[], double self_inter)
{
	int				i;
	double			t;
	double		mesh_mag;
	double		light_mag;
	t_ray_vector	intersect_pt;

	if (mesh->type == O_SP)
	{
		// t_ray tmp =  *n_light_ray;
		// t_ray *light_ray = &tmp;

		// normalize_vector(light_ray->dir_vect.axis);		
		i = -1;
		while (++i < data->sp_nbr)
		{	
			if (mesh->ref && (void *) &data->spheres[i] != mesh->ref && !is_same_sphere_space(&data->spheres[i], mesh->ref))
			{
				t = is_intersect_sphere(light_rays[1], &data->spheres[i], NULL);
				if( (t && !self_inter)||( t && self_inter && self_inter < data->spheres[i].t2))
				{
					get_local_intersect_point(light_rays[1], t, &intersect_pt);
					light_mag = get_vector_magnitude(light_rays[0]->dir_vect.axis);
					mesh_mag = get_vector_magnitude(intersect_pt.axis);
					if (mesh_mag - 1e-5 < light_mag)
						return (1);
				}
			}
		}
		return (0);
	}	
		
		i = -1;
		while (++i < data->sp_nbr)
		{				
			t = is_intersect_sphere(light_rays[1], &data->spheres[i], NULL);
			if(t)
			{
				get_local_intersect_point(light_rays[1], t, &intersect_pt);
				light_mag = get_vector_magnitude(light_rays[0]->dir_vect.axis);
				mesh_mag = get_vector_magnitude(intersect_pt.axis);
				if (mesh_mag - 1e-5 < light_mag)
					return (1);
			}			
		}
		return (0);
}

int	has_cylinder_shadow(t_data *data, t_obj *mesh, t_ray *n_light_ray, double self_inter)
{
	int				i;
	double			t;
	double		mesh_mag;
	double		light_mag;
	t_ray_vector	intersect_pt;

		t_ray tmp =  *n_light_ray;
		t_ray *light_ray = &tmp;
		//normalize_vector(light_ray->dir_vect.axis);
	if (mesh->type == O_CY)
	{
		t_cylinder cylinder = *(t_cylinder *)mesh->ref;
		// double int_t = is_intersect_cylinder(light_ray, &cylinder, NULL);
		i = -1;
		while (++i < data->cy_nbr)
		{
			if (mesh->ref && (void *) &data->cylinders[i] != mesh->ref && !is_same_cylinder_space(&data->cylinders[i], &cylinder))
			{
				t = is_intersect_cylinder(light_ray, &data->cylinders[i], NULL);
				if( (t && self_inter < 1e-3)||( t && self_inter && self_inter < data->cylinders[i].t2))
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
	i = -1;
	while (++i < data->cy_nbr)
	{		
		t = is_intersect_cylinder(light_ray, &data->cylinders[i], NULL);
		//if( (t && self_inter < 1e-3)||( t && self_inter && self_inter < data->cylinders[i].t2))

		if (t)
		{
			get_local_intersect_point(n_light_ray, t, &intersect_pt);
			light_mag = get_vector_magnitude(n_light_ray->dir_vect.axis);
			mesh_mag = get_vector_magnitude(intersect_pt.axis);
			if (mesh_mag - 1e-5 < light_mag)
				return (1);
		}			
	}
	return (0);
}

int	has_plane_shadow(t_data *data, t_obj *mesh, t_ray *light_ray)
{
	int				i;
	double			t;
	double		mesh_mag;
	double		light_mag;
	t_ray_vector	intersect_pt;

	if (mesh->type == O_PL)
	{
		i = -1;
		while (++i < data->pl_nbr)
		{
			if (mesh->ref && (void *) &data->planes[i] != mesh->ref && !is_same_plane_space(&data->planes[i], mesh->ref))
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

	i = -1;
	while (++i < data->pl_nbr)
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
	return (0);
}

int	has_shadow(t_data *data, t_obj *mesh, t_ray *light_ray)
{
	double 	self_inter;
	t_sphere 	sph_cpy;
	t_cylinder 	cyl_cpy;
	t_ray 		light_ray_norm;

	light_ray_norm = *light_ray;
	normalize_vector(light_ray_norm.dir_vect.axis);

	if (mesh->type == O_SP)
	{
		sph_cpy = *(t_sphere *) mesh->ref;
		self_inter = is_intersect_sphere(&light_ray_norm, &sph_cpy, NULL);
	}
	else if (mesh->type == O_CY)
	{		
		cyl_cpy = *(t_cylinder *) mesh->ref;
		self_inter = is_intersect_cylinder(&light_ray_norm, &cyl_cpy, NULL);
	}
	if (has_sphere_shadow(data, mesh, (t_ray *[]){light_ray, &light_ray_norm}, self_inter))
		return (1);
	if (has_cylinder_shadow(data, mesh, light_ray, self_inter))
		return (1);
	if (has_plane_shadow(data, mesh, light_ray))
		return (1);
	return (0);
}