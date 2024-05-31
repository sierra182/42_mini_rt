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
	t_ray_vector	inter_pt;
		
	i = -1;
	while (++i < data->sp_nbr)
	{	
		if (mesh->ref && (void *) &data->spheres[i] != mesh->ref)
		{
			t = is_intersect_sphere(light_rays[1], &data->spheres[i], NULL);
			if (mesh->type == CY && ((t_cylinder *)mesh->ref)->cyl_or_discs == cylinder)
			{
			if (((t_cylinder *)mesh->ref)->which_t == 1)
			{
			  if( (t && !self_inter)
				
					||( t && self_inter < data->spheres[i].t2))
				// if (t && mesh->type != O_SP || t && mesh->type == O_SP && !self_inter)
				{
					get_local_intersect_point(light_rays[1], t, &inter_pt);
					light_mag = get_vector_magnitude(light_rays[0]->dir_vect.axis);
					mesh_mag = get_vector_magnitude(inter_pt.axis);
					if (mesh_mag - 1e-5 < light_mag)
						return (1);
				}
			}
			}
			else 
			{
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
	}
	return (0);
}

int	has_cylinder_shadow(t_data *data, t_obj *mesh, t_ray *light_rays[],
	double self_inter)
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
			//if ((t && self_inter < 1e-3)
				//|| ( t && self_inter && self_inter < data->cylinders[i].t2))
			// if (t && mesh->type != O_CY || t && mesh->type == O_CY && !self_inter)
		//	if (((t_cylinder *)mesh->ref)->which_t == 1)// && ((t_cylinder *)mesh->ref)->cyl_or_discs == cylinder)
			// {
			// 	if (t && !self_inter ||
			// 	t && self_inter < data->cylinders[i].t2 && data->cylinders[i].cyl_or_discs == cylinder
			// 	|| t &&  data->cylinders[i].cyl_or_discs == discs && self_inter < t)
			// 	{
			// 		get_local_intersect_point(light_rays[1], t, &inter_pt);
			// 		light_mag = get_vector_magnitude(light_rays[0]->dir_vect.axis);
			// 		mesh_mag = get_vector_magnitude(inter_pt.axis);
			// 		if (mesh_mag - 1e-5 < light_mag)
			// 			return (1);
			// 	}
			// }
			// else 
			// {
				if (t)
				{
					get_local_intersect_point(light_rays[1], t, &inter_pt);
					light_mag = get_vector_magnitude(light_rays[0]->dir_vect.axis);
					mesh_mag = get_vector_magnitude(inter_pt.axis);
					if (mesh_mag - 1e-5 < light_mag)
						return (1);
			// 	}

			 }
		}
	}
	return (0);
}

int	has_plane_shadow(t_data *data, t_obj *mesh, t_ray *light_ray,
	double self_inter)
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
			t = is_intersect_plane(light_ray, &data->planes[i], NULL);
			if (t)
			{
				get_local_intersect_point(light_ray, t, &inter_pt);
				light_mag = get_vector_magnitude(light_ray->dir_vect.axis);
				mesh_mag = get_vector_magnitude(inter_pt.axis);
				if (mesh_mag - 1e-5 < light_mag)
					return (1);
			}
		}
	}
	return (0);
}
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);

int	has_shadow(t_data *data, t_obj *mesh, t_ray *light_ray)
{
	double 	self_inter;
	t_sphere 	sph_cpy;
	t_cylinder 	cyl_cpy;
	t_ray 		light_ray_norm;

	self_inter = 0.0;
	light_ray_norm = *light_ray;
	normalize_vector(light_ray_norm.dir_vect.axis);
	if (mesh->type == O_SP)
	{
		sph_cpy = *(t_sphere *) mesh->ref;
		self_inter = is_intersect_sphere(&light_ray_norm, &sph_cpy, NULL);
		if (self_inter && sph_cpy.which_t == 2)
			get_intersect_point(&light_ray_norm, sph_cpy.t2, &light_ray_norm.origin_vect);
	}
	else if (mesh->type == O_CY)
	{		
		cyl_cpy = *(t_cylinder *) mesh->ref;
		self_inter = is_intersect_cylinder(&light_ray_norm, &cyl_cpy, NULL);
		
	}
	if ((has_sphere_shadow(data, mesh,
		(t_ray *[]){light_ray, &light_ray_norm}, self_inter))
		|| (has_cylinder_shadow(data, mesh,
		(t_ray *[]){light_ray, &light_ray_norm}, self_inter))
		|| (has_plane_shadow(data, mesh, light_ray, self_inter)))
		return (1);
	return (0);
}
