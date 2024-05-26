/* ************************************************************************** */

#include "x_mini_struct.h"
#include "math.h"
#include "x_linear_algebra.h"

double	solve_quadratic_equation(t_ray *ray, t_cylinder *cyl, double *discrim);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
double	scalar_product(double a[], double b[]);
void	add_vector(double a[], double b[], double sum_vect[]);
void	subtract_vector(double a[], double b[], double subt_vect[]);
void	scale_vector(double vect[], double scaler, double scaled_vect[]);
void	normalize_vector(double vector[]);
double	distance_between_points(t_ray_vector *point1, t_matrix_vector *point2);
double	get_t_from_point(t_ray *ray, t_ray_vector *point);
double	compute_return_value_intersect_disc_plans(double tmp1, double tmp2);
double	compute_return_value_is_intersect_cylinder(double t[],
			t_cylinder *cyl, double proj[]);
double	is_intersect_cylinder(t_ray *ray, void *input_cyl, t_ray_vector *tt);

#define EPSILON 1e-6

double	which_t(double a, double b, double discrim, int *which_t)
{
	if (discrim < 0)
		return (*which_t = 0, 0.0);
	if ((-b - sqrt(discrim)) / (2 * a) > 0.0)
		return (*which_t = 1, (-b - sqrt(discrim)) / (2 * a));
	else if ((-b + sqrt(discrim)) / (2 * a) > 0.0)
		return (*which_t = 2, (-b + sqrt(discrim)) / (2 * a));
	else
		return (*which_t = 0, 0.0);
}
/**========================================================================
 *                             IS_INTERSECT
 *  How to solve the cylinder/discs display order problem?
 *  => refactor and treat discs just as another type of objects, just as
 *  spheres, planes and cylinders, so that they are treated independantly.
 *========================================================================**/
/**========================================================================
 *                           IS_INTERSECT_SPHERE
 *========================================================================**/

double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i)
{
	t_ray_vector	sphere_ray_vect;
	double			num[3];
	double			discrim;
	t_sphere		*sphere;

	sphere = (t_sphere *)input_sphere;
	subtract_vector(ray->origin_vect.axis, sphere->origin_vect.axis,
		sphere_ray_vect.axis);
	num[0] = scalar_product(ray->dir_vect.axis, ray->dir_vect.axis);
	num[1] = scalar_product(sphere_ray_vect.axis, ray->dir_vect.axis) * 2;
	num[2] = scalar_product(sphere_ray_vect.axis, sphere_ray_vect.axis)
		- sphere->square_radius;
	discrim = num[1] * num[1] - 4 * num[0] * num[2];
	return (which_t(num[0], num[1], discrim, &sphere->which_t));
}

/**========================================================================
 *                           IS_INTERSECT_PLANE
 *========================================================================**/
double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i)
{
	double			t;
	t_ray_vector	a;
	double			num;
	double			den;
	t_plane			*plane;

	plane = (t_plane *)input_plane;
	normalize_vector(plane->norm_vect.axis);
	subtract_vector(plane->origin_vect.axis, ray->origin_vect.axis, a.axis);
	num = scalar_product(a.axis, plane->norm_vect.axis);
	den = scalar_product(ray->dir_vect.axis, plane->norm_vect.axis);
	if (fabs(den) > EPSILON)
	{
		t = num / den;
		if (t >= 0.0)
		{
			if (i)
			{
				scale_vector(ray->dir_vect.axis, t, i->axis);
				add_vector(ray->origin_vect.axis, i->axis, i->axis);
			}
			return (t);
		}
	}
	return (0);
}

/**========================================================================
 *                           SOLVE_QUADRATIC_EQUATION
 *========================================================================**/
double	solve_quadratic_equation(t_ray *ray, t_cylinder *cyl, double *discrim)
{
	t_ray_vector	cr;
	double			a;
	double			b;
	double			c;	
	double			t1;

	normalize_vector(cyl->axis_vect.axis);
	subtract_vector(ray->origin_vect.axis, cyl->origin_vect.axis, cr.axis);
	a = scalar_product(ray->dir_vect.axis, ray->dir_vect.axis)
		- pow(scalar_product(ray->dir_vect.axis, cyl->axis_vect.axis), 2);
	b = 2 * (scalar_product(ray->dir_vect.axis, cr.axis) - scalar_product
			(ray->dir_vect.axis, cyl->axis_vect.axis) * scalar_product
			(cr.axis, cyl->axis_vect.axis));
	c = scalar_product(cr.axis, cr.axis) - pow(scalar_product(cr.axis,
				cyl->axis_vect.axis), 2) - cyl->square_radius;
	*discrim = b * b - 4 * a * c;
	return (which_t(a, b, *discrim, &cyl->which_t));
}
