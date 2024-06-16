# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"
# include <math.h>
/**========================================================================
 *                          IS_INTERSECT_TRIANGLE
 *========================================================================**/
double	is_intersect_triangle(t_ray *ray, void *input_triangle)
{
	t_triangle		*triangle;
	t_ray_vector	e1;
	t_ray_vector	e2;
	t_ray_vector	p;
	t_ray_vector	t_vect;
	t_ray_vector	q;
	double			det;
	double 			inv_det;
	double			u;
	double			v;
	double 			t;
	const double	epsilon = 1e-6;

	triangle = (t_triangle *) input_triangle;
	// printf("%f, %f, %f :  %f, %f, %f : %f, %f, %f : %d, %d, %d\n",
	// triangle->point_a.axis[0], triangle->point_a.axis[1], triangle->point_a.axis[2], 
	// triangle->point_b.axis[0], triangle->point_b.axis[1], triangle->point_b.axis[2], 
	// triangle->point_c.axis[0], triangle->point_c.axis[1], triangle->point_c.axis[2], 
	// triangle->color.rgb[0], triangle->color.rgb[1], triangle->color.rgb[2]);
	subtract_vector(triangle->point_b.axis, triangle->point_a.axis, e1.axis);
	subtract_vector(triangle->point_c.axis, triangle->point_a.axis, e2.axis);
	cross_product(ray->dir_vect.axis, e2.axis, p.axis);
	det = scalar_product(e1.axis, p.axis); 
	if (fabs(det) < epsilon)
		return (0.0);
	inv_det = 1.0 / det;
	subtract_vector(ray->origin_vect.axis, triangle->point_a.axis,
		t_vect.axis);
	u = scalar_product(t_vect.axis, p.axis) * inv_det; 
	if (u < -epsilon || u > 1 + epsilon)
		return (0.0);
	cross_product(t_vect.axis, e1.axis, q.axis);
	v = scalar_product(ray->dir_vect.axis, q.axis) * inv_det; 
	if (v < -epsilon || u + v > 1 + epsilon)
		return (0.0);
	t = scalar_product(e2.axis, q.axis) * inv_det; 
	if (t > 1e-5)
		return (t);
	return (0.0);
}