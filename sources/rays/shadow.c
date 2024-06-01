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

// int	is_in_cyl_diam( t_cylinder *cyl, t_ray_vector *normal, double mesh[])
// {
// 	t_ray_vector	subt_vect;
// 	t_ray_vector	inter_vect;
	
// 	t_ray			ray;

// 	// ray.dir_vect = *normal;
// 	cast_vector_mat_ray(&cyl->axis_vect, &ray.dir_vect);
// 	cast_vector_mat_ray(&cyl->origin_vect, &ray.origin_vect);
// 	subtract_vector(mesh, cyl->origin_vect.axis, subt_vect.axis);
// 		 normalize_vector(ray.dir_vect.axis);

// 	//get_intersect_point(&ray, scalar_product(normal->axis, subt_vect.axis), &inter_vect);
// 	 scale_vector(ray.dir_vect.axis, scalar_product(ray.dir_vect.axis, subt_vect.axis), inter_vect.axis);
// 	subtract_vector(inter_vect.axis, subt_vect.axis, subt_vect.axis);
// 	if (get_vector_magnitude(subt_vect.axis) <= cyl->diameter * 0.5)
// 		return (1);
// 	else
// 		return (0);
// }

// void	print_delay(t_ray_vector *subt_vect, double diam)
// {
// 	static int delay;

// 	delay = (delay + 1) % 1800;
// 	if (!delay)
// 		printf("mag:%f rayon:%f\n", get_vector_magnitude(subt_vect->axis), diam * 0.5 );
// }

// int is_in_cyl_height(t_ray_vector *normal, t_cylinder *cyl, double mesh[])
// {
// 	t_ray_vector	subt_vect;

// 	subtract_vector(mesh, cyl->origin_vect.axis, subt_vect.axis);
// 	// normalize_vector(subt_vect.axis);
// 	if (fabs(scalar_product(normal->axis, subt_vect.axis)) < cyl->height * 0.5)	
// 	{
// 		 // printf("IN\n");
// 		return (1);
// 	}	
// 	//   printf("OUT\n");
// 	return (0);
// }

// int	is_in_cylinder(t_ray_vector *normal, t_cylinder *cyl, double mesh[])
// {
// 	return (is_in_cyl_height(normal, cyl, mesh)
// 		&& is_in_cyl_diam(cyl, normal, mesh));
// }
// int	are_light_and_cam_in_different_cyl_space(t_ray_vector *normal, t_spotlight *light, t_cylinder *cyl, t_cam *cam)
// {
// 	if (is_in_cylinder(normal, cyl, light->origin_vect.axis)
// 		&& is_in_cylinder(normal, cyl, cam->origin_vect.axis))	
// 	{
// 	//	printf("same IN\n");	
// 		return (0);
// 	}
// 	if (!is_in_cylinder(normal, cyl, light->origin_vect.axis)
// 		&& !is_in_cylinder(normal, cyl, cam->origin_vect.axis))	
// 	{
// 	//	printf("same OUT\n");	
// 		return (0);
// 	}
// 	//printf("different space\n");	
// 	return (1);
// }
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
			// if (mesh->type == CY && ((t_cylinder *)mesh->ref)->cyl_or_discs == cylinder)
			// {
			// if (((t_cylinder *)mesh->ref)->which_t == 1)
			// {
			//   if( (t && !self_inter)
				
			// 		||( t && self_inter < data->spheres[i].t2))
			// 	// if (t && mesh->type != O_SP || t && mesh->type == O_SP && !self_inter)
			// 	{
			// 		get_local_intersect_point(light_rays[1], t, &inter_pt);
			// 		light_mag = get_vector_magnitude(light_rays[0]->dir_vect.axis);
			// 		mesh_mag = get_vector_magnitude(inter_pt.axis);
			// 		if (mesh_mag - 1e-5 < light_mag)
			// 			return (1);
			// 	}
			// }
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
int	is_in_cylinder(t_ray_vector *normal, t_cylinder *cyl, double mesh[]);

int	has_shadow(t_data *data, t_ray_vector *normal, t_obj *mesh, t_ray *light_ray)
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
		if (self_inter && ((t_sphere *) mesh->ref)->which_t == 1)
			get_intersect_point(&light_ray_norm, sph_cpy.t2, &light_ray_norm.origin_vect);
	}
	else if (mesh->type == O_CY)
	{		
		cyl_cpy = *(t_cylinder *) mesh->ref;
		self_inter = is_intersect_cylinder(&light_ray_norm, &cyl_cpy, NULL);
		if (self_inter && !is_in_cylinder(normal, &cyl_cpy, data->cam.origin_vect.axis))
		 
		// if (self_inter && ((t_cylinder *) mesh->ref)->which_t == 1 && ((t_cylinder *) mesh->ref)->cyl_or_discs == cylinder 
		// || (self_inter && ((t_cylinder *) mesh->ref)->which_t == 1 && ((t_cylinder *) mesh->ref)->cyl_or_discs == discs)
		// )
			get_intersect_point(&light_ray_norm, cyl_cpy.t2, &light_ray_norm.origin_vect);
	}
	if ((has_sphere_shadow(data, mesh,
		(t_ray *[]){light_ray, &light_ray_norm}, self_inter))
		|| (has_cylinder_shadow(data, mesh,
		(t_ray *[]){light_ray, &light_ray_norm}, self_inter))
		|| (has_plane_shadow(data, mesh, light_ray, self_inter)))
		return (1);
	return (0);
}
