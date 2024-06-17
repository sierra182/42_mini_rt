#include "is_intersect_triangle_bonus.h"

/**========================================================================
 *                          IS_INTERSECT_TRIANGLE
 *========================================================================**/
double	is_intersect_triangle(t_ray *ray, void *input_triangle,
	t_ray_vector *i)
{
	t_triangle		*triangle;
	t_ray_vector	p;
	t_ray_vector	t_vect;
	t_ray_vector	q;
	double			det;
	double 			inv_det;
	double			u;
	double			v;
	double 			t;
	const double	epsilon = 1e-6;
	(void) i;
	triangle = (t_triangle *) input_triangle;	
	subtract_vector(triangle->point_b.axis, triangle->point_a.axis,
		triangle->e1.axis);
	subtract_vector(triangle->point_c.axis, triangle->point_a.axis,
		triangle->e2.axis);
	cross_product(ray->dir_vect.axis, triangle->e2.axis, p.axis);
	det = scalar_product(triangle->e1.axis, p.axis); 
	if (fabs(det) < epsilon)
		return (0.0);
	inv_det = 1.0 / det;
	subtract_vector(ray->origin_vect.axis, triangle->point_a.axis,
		t_vect.axis);
	u = scalar_product(t_vect.axis, p.axis) * inv_det; 
	if (u < -epsilon || u > 1 + epsilon)
		return (0.0);
	cross_product(t_vect.axis, triangle->e1.axis, q.axis);
	v = scalar_product(ray->dir_vect.axis, q.axis) * inv_det; 
	if (v < -epsilon || u + v > 1 + epsilon)
		return (0.0);
	t = scalar_product(triangle->e2.axis, q.axis) * inv_det; 
	if (t > 1e-5)
		return (t);
	return (0.0);
}