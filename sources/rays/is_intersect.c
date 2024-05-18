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
 *                           is_intersect_sphere
 *========================================================================**/

double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i)
{
	t_ray_vector	sphere_ray_vect;
	double			a;
	double			b;
	double			c;	
	double			discrim;
	
	t_sphere *sphere = (t_sphere *)input_sphere;
	subtract_vector(ray->origin_vect.axis, sphere->origin_vect.axis,
		sphere_ray_vect.axis);
	a = scalar_product(ray->dir_vect.axis, ray->dir_vect.axis);
	b = scalar_product(sphere_ray_vect.axis, ray->dir_vect.axis) * 2;
	c = scalar_product(sphere_ray_vect.axis, sphere_ray_vect.axis)
		- sphere->square_radius;
	discrim = b * b - 4 * a * c;
	return (which_t(a, b, discrim, &sphere->which_t));
}

/**========================================================================
 *                           is_intersect_plane
 *========================================================================**/
double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i)
{
	double			t;
	t_ray_vector	a;
	double			num;
	double			den;

	t_plane *plane = (t_plane *)input_plane;
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
 *                           intersect_disc_plans
 *========================================================================**/
int	intersect_disc_plans(t_ray *ray, t_cylinder *cyl, t_ray_vector	*i)
{
	t_plane			plane_1;
	t_plane			plane_2;
	t_matrix_vector	scaled_v;

	plane_1.norm_vect = cyl->axis_vect;
	plane_2.norm_vect = cyl->axis_vect;
	scale_vector(cyl->axis_vect.axis, cyl->height * 0.5, scaled_v.axis);
	add_vector(scaled_v.axis, cyl->origin_vect.axis, plane_1.origin_vect.axis);
	scale_vector(cyl->axis_vect.axis, cyl->height * -0.5, scaled_v.axis);
	add_vector(scaled_v.axis, cyl->origin_vect.axis, plane_2.origin_vect.axis);
	if ((is_intersect_plane(ray, &plane_1, i) && distance_between_points(i, &plane_1.origin_vect) <= cyl->radius) || (is_intersect_plane(ray, &plane_2, i) && distance_between_points(i, &plane_2.origin_vect) <= cyl->radius))
	{
		return (1);
	}
	return (0);
}

/**========================================================================
 *                           is_intersect_cylinder
 *========================================================================**/
double	is_intersect_cylinder(t_ray *ray, void *input_cyl, t_ray_vector *t)
{
	double			discrim;
	double			t1;
	t_ray_vector	i;
	double			origin_proj;
	double			proj;

	t_cylinder *cyl = (t_cylinder *)input_cyl;
	t1 = solve_quadratic_equation(ray, cyl, &discrim);
	if (discrim < 0)
		return (0.0);
	get_intersect_point(ray, t1, &i);
	cyl->intersec_point.axis[0] = i.axis[0];
	cyl->intersec_point.axis[1] = i.axis[1];
	cyl->intersec_point.axis[2] = i.axis[2];
	proj = scalar_product(i.axis, cyl->axis_vect.axis);
	cyl->proj = proj;
	origin_proj = scalar_product(cyl->origin_vect.axis, cyl->axis_vect.axis);
	if (intersect_disc_plans(ray, cyl, &i))
		return (cyl->cyl_or_discs = discs, get_t_from_point(ray, &i));
	if (proj < origin_proj - cyl->height * 0.5
		|| proj > origin_proj + cyl->height * 0.5)
		return (0.0);
	return (cyl->cyl_or_discs = cylinder, t1);
}

/**========================================================================
 *                           solve_quadratic_equation
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
	t1 = (-b - sqrt(*discrim)) / (2 * a);
	return (t1);
}
