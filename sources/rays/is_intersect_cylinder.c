#include "se_mini_struct.h"
#include "math.h"
#include "x_linear_algebra.h"

double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
double	distance_between_points(t_ray_vector *point1, t_matrix_vector *point2);
double	get_t_from_point(t_ray *ray, t_ray_vector *point);
double	compute_return_value_intersect_disc_plans(double tmp1, double tmp2);
double	compute_return_value_is_intersect_cylinder(double t[],
			t_cylinder *cyl, double proj[]);
double	solve_quadratic_equation(t_ray *ray, t_cylinder *cyl, double *discrim);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);

/**========================================================================
 *                           INTERSECT_DISC_PLANS
 *========================================================================**/
double	intersect_disc_plans(t_ray *ray, t_cylinder *cyl, t_ray_vector	*i)
{
	t_plane			plane_1;
	t_plane			plane_2;
	t_matrix_vector	scaled_v;
	double			tmp1;
	double			tmp2;

	tmp1 = 0;
	tmp2 = 0;
	plane_1.norm_vect = cyl->axis_vect;
	plane_2.norm_vect = cyl->axis_vect;
	scale_vector(cyl->axis_vect.axis, cyl->height * 0.5, scaled_v.axis);
	add_vector(scaled_v.axis, cyl->origin_vect.axis, plane_1.origin_vect.axis);
	scale_vector(cyl->axis_vect.axis, cyl->height * -0.5, scaled_v.axis);
	add_vector(scaled_v.axis, cyl->origin_vect.axis, plane_2.origin_vect.axis);
	if ((is_intersect_plane(ray, &plane_1, i) && distance_between_points
			(i, &plane_1.origin_vect) <= cyl->radius))
		tmp1 = get_t_from_point(ray, i);
	if ((is_intersect_plane(ray, &plane_2, i) && distance_between_points
			(i, &plane_2.origin_vect) <= cyl->radius))
		tmp2 = get_t_from_point(ray, i);
	return (compute_return_value_intersect_disc_plans(tmp1, tmp2));
}

/**========================================================================
 *                    COMPUTE_RETURN_VALUE_INTERSECT_DISC_PLANS
 *========================================================================**/
double	compute_return_value_intersect_disc_plans(double tmp1, double tmp2)
{
	if (tmp1 && tmp2)
	{
		if (tmp1 && tmp1 < tmp2)
			return (tmp1);
		return (tmp2);
	}
	if (tmp1)
		return (tmp1);
	if (tmp2)
		return (tmp2);
	return (0);
}

/**========================================================================
 *                           IS_INTERSECT_CYLINDER
 * vars t & proj where declared as arrays of size 2 for norminette compliance
 * 
 *========================================================================**/
double	is_intersect_cylinder(t_ray *ray, void *input_cyl, t_ray_vector *tt)
{
	double			discrim;
	double			t[2];
	t_ray_vector	i;
	double			proj[2];
	t_cylinder		*cyl;

	cyl = (t_cylinder *)input_cyl;
	t[0] = solve_quadratic_equation(ray, cyl, &discrim);
	if (discrim < 0)
		return (0.0);
	get_intersect_point(ray, t[0], &i);
	cyl->intersec_point.axis[0] = i.axis[0];
	cyl->intersec_point.axis[1] = i.axis[1];
	cyl->intersec_point.axis[2] = i.axis[2];
	proj[0] = scalar_product(i.axis, cyl->axis_vect.axis);
	cyl->proj = proj[0];
	proj[1] = scalar_product(cyl->origin_vect.axis, cyl->axis_vect.axis);
	if (proj[0] < proj[1] - cyl->height * 0.5
		|| proj[0] > proj[1] + cyl->height * 0.5)
		t[0] = BIG_VALUE;
	t[1] = intersect_disc_plans(ray, cyl, &i);
	return (compute_return_value_is_intersect_cylinder(t, cyl, proj));
}

/**========================================================================
 *                  COMPUTE_RETURN_VALUE_IS_INTERSECT_CYLINDER
 *========================================================================**/
double	compute_return_value_is_intersect_cylinder(double t[],
	t_cylinder *cyl, double proj[])
{
	if (t[1] && t[1] < t[0])
		return (cyl->cyl_or_discs = discs, cyl->which_t = 1, t[1]);
	else if (proj[0] < proj[1] - cyl->height * 0.5
		|| proj[0] > proj[1] + cyl->height * 0.5)
		return (0.0);
	else
		return (cyl->cyl_or_discs = cylinder, t[0]);
}
