# include "se_mini_struct.h"
# include "x_linear_algebra.h"

// int	is_same_sphere_space(t_sphere *a, t_sphere *b)
// {
// 	return (is_equal_vector(a->origin_vect.axis, b->origin_vect.axis)
// 		&& a->diameter == b->diameter);
// }

// int	is_same_plane_space(t_plane *a, t_plane *b)
// {
// 	return (is_equal_vector(a->origin_vect.axis, b->origin_vect.axis)
// 		&& is_equal_vector(a->norm_vect.axis, b->norm_vect.axis));
// }

// int	is_same_cylinder_space(t_cylinder *a, t_cylinder *b)
// {	
// 	double	distance;
// 	t_matrix_vector	subt_vect;
// t_matrix_vector	tmp1;
// t_matrix_vector	tmp2;
// 	subtract_vector(a->origin_vect.axis, b->origin_vect.axis, subt_vect.axis);
// 	distance = get_vector_magnitude(subt_vect.axis);
// 	cross_product(&subt_vect, &a->axis_vect, &tmp1);
// 	cross_product(&subt_vect, &b->axis_vect, &tmp2);
// 	return (a->diameter == b->diameter
// 		&& 
// 		((is_equal_vector(a->origin_vect.axis, b->origin_vect.axis)
// 	 	&& is_equal_vector(a->axis_vect.axis, b->axis_vect.axis))
// 		|| ((are_collinear_vectors(&tmp1, 1e-4)
// 		&& are_collinear_vectors(&tmp2, 1e-4) && distance > 0)
// 		&& distance <= (a->height + b->height) * 0.5)
// 		|| ((are_collinear_vectors(&a->axis_vect, 1e-4)
// 		&& are_collinear_vectors(&b->axis_vect, 1e-4) && distance == 0)
// 		))	
// 		);
// }

int	is_sphere_surface_between(t_sphere *sphere, t_spotlight *spotlight)
{
	t_matrix_vector	subt_vect;

	subtract_vector(spotlight->origin_vect.axis, sphere->origin_vect.axis, subt_vect.axis);	
	return ((get_vector_magnitude(subt_vect.axis) > sphere->diameter * 0.5
	&& sphere->which_t == 2) || ((get_vector_magnitude(subt_vect.axis) < sphere->diameter * 0.5
	&& sphere->which_t == 1)));
}

// int	is_cylinder_surface_between(t_cylinder *cyl, t_spotlight *spotlight)
// {
// 	t_matrix_vector	subt_vect;

// 	subtract_vector(spotlight->origin_vect.axis, cyl->origin_proj.axis, subt_vect.axis);	
// 	return ((get_vector_magnitude(subt_vect.axis) > cyl->radius
// 	&& cyl->which_t == 2) || ((get_vector_magnitude(subt_vect.axis) < cyl->radius
// 	&& cyl->which_t == 1)));
// }

int	is_cylinder_surface_between( t_cylinder *cyl, t_ray_vector *normal, double mesh[])
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