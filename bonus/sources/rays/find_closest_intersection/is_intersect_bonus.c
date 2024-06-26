/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_intersect_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:47:48 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 15:47:49 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is_intersect_bonus.h"

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

	(void) i;
	sphere = (t_sphere *)input_sphere;
	subtract_vector(ray->origin_vect.axis, sphere->origin_vect.axis,
		sphere_ray_vect.axis);
	num[0] = scalar_product(ray->dir_vect.axis, ray->dir_vect.axis);
	num[1] = scalar_product(sphere_ray_vect.axis, ray->dir_vect.axis) * 2;
	num[2] = scalar_product(sphere_ray_vect.axis, sphere_ray_vect.axis)
		- sphere->square_radius;
	discrim = num[1] * num[1] - 4 * num[0] * num[2];
	return (which_t((double []){discrim, num[0], num[1]}, &sphere->which_t,
		(double *[]){&sphere->t1, &sphere->t2}));
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
	self_normalize_vector(plane->norm_vect.axis);
	subtract_vector(plane->origin_vect.axis, ray->origin_vect.axis, a.axis);
	num = scalar_product(a.axis, plane->norm_vect.axis);
	den = scalar_product(ray->dir_vect.axis, plane->norm_vect.axis);
	if (fabs(den) > EPSILON)
	{
		t = num / den;
		if (t >= 1e-6)
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

	self_normalize_vector(cyl->axis_vect.axis);
	subtract_vector(ray->origin_vect.axis, cyl->origin_vect.axis, cr.axis);
	a = scalar_product(ray->dir_vect.axis, ray->dir_vect.axis)
		- pow(scalar_product(ray->dir_vect.axis, cyl->axis_vect.axis), 2);
	b = 2 * (scalar_product(ray->dir_vect.axis, cr.axis) - scalar_product
			(ray->dir_vect.axis, cyl->axis_vect.axis) * scalar_product
			(cr.axis, cyl->axis_vect.axis));
	c = scalar_product(cr.axis, cr.axis) - pow(scalar_product(cr.axis,
				cyl->axis_vect.axis), 2) - cyl->square_radius;
	*discrim = b * b - 4 * a * c;
	return (which_t((double []){*discrim, a, b}, &cyl->which_t,
		(double *[]){&cyl->t1, &cyl->t2}));
}

/**========================================================================
 *                          IS_INTERSECT_TRIANGLE
 *========================================================================**/
double	is_intersect_triangle(t_ray *ray, void *input_triangle,
	t_ray_vector *i)
{
	t_tri	tri;

	tri.triangle = (t_triangle *) input_triangle;
	subtract_vector(tri.triangle->point_b.axis, tri.triangle->point_a.axis,
		tri.triangle->e1.axis);
	subtract_vector(tri.triangle->point_c.axis, tri.triangle->point_a.axis,
		tri.triangle->e2.axis);
	cross_product(ray->dir_vect.axis, tri.triangle->e2.axis, tri.p.axis);
	tri.det = scalar_product(tri.triangle->e1.axis, tri.p.axis);
	if (fabs(tri.det) < TRI_E)
		return (0.0);
	tri.inv_det = 1.0 / tri.det;
	subtract_vector(ray->origin_vect.axis, tri.triangle->point_a.axis,
		tri.t_vect.axis);
	tri.u = scalar_product(tri.t_vect.axis, tri.p.axis) * tri.inv_det;
	if (tri.u < -TRI_E || tri.u > 1 + TRI_E)
		return (0.0);
	cross_product(tri.t_vect.axis, tri.triangle->e1.axis, tri.q.axis);
	tri.v = scalar_product(ray->dir_vect.axis, tri.q.axis) * tri.inv_det;
	if (tri.v < -TRI_E || tri.u + tri.v > 1 + TRI_E)
		return (0.0);
	tri.t = scalar_product(tri.triangle->e2.axis, tri.q.axis) * tri.inv_det;
	if (tri.t > TRI_E)
		return (tri.t);
	return ((void) i, 0.0);
}

/**========================================================================
 *                           WHICH_T
 *========================================================================**/
double	which_t(double eq_values[], int *which_t, double *tt[])
{
	if (eq_values[0] < 0)
		return (*which_t = 0, 0.0);
	*tt[0] = (-eq_values[2] - sqrt(eq_values[0])) / (2 * eq_values[1]);
	*tt[1] = (-eq_values[2] + sqrt(eq_values[0])) / (2 * eq_values[1]);
	if (*tt[0] > 1e-6)
		return (*which_t = 1, *tt[0]);
	else if (*tt[1] > 1e-6)
		return (*which_t = 2, *tt[1]);
	else
		return (*which_t = 0, 0.0);
}
