# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

double	is_intersect_triangle(t_ray *ray, void *input_triangle, t_ray_vector *i)
{
	t_triangle		*triangle;
	t_matrix_vector	e1;
	t_matrix_vector	e2;
	t_matrix_vector	p;
	t_matrix_vector	t_vect;
	t_matrix_vector	q;
	double			det;
	double 			inv_det;
	double			u;
	double			v;
	double 			t;

	triangle = (t_triangle *) input_triangle;
	subtract_vector(triangle->point_b.axis, triangle->point_a.axis, e1.axis);
	subtract_vector(triangle->point_c.axis, triangle->point_a.axis, e2.axis);
	cross_product(&ray->dir_vect, &e2, &p)
	det = scalar_product(e1.axis, p.axis); // norm ?
	if (det < 1e-5 && det > -1e-5) // proche de zero...
		return (0.0);
	inv_det = 1 / det;
	subtract_vector(ray->origin_vect, triangle->point_a.axis, t_vect.axis);
	u = scalar_product(t.axis, p.axis) * inv_det; // norm...
	if (u < 0 || u > 1) // precision ?
		return (0.0);
	cross_product(&t_vect, &e1, &q);
	v = scalar_product(d.axis, q.axis) * inv_det; // norm...
	if (v < 0 || u + v > 1) // precision ?
		return (0.0);
	t = scalar_product(e2.axis, q.axis) * inv_det; // norm...
	if (t > 1e-5)
		return (t);
}