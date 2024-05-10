#include "math.h"
#include "x_mini_struct.h"

void	subtract_vector(double a[], double b[], double subt_vect[]);

double	distance_between_points(t_ray_vector *point1, t_matrix_vector *point2)
{
	double	dx;
	double	dy;
	double	dz;

	dx = point2->axis[0] - point1->axis[0];
	dy = point2->axis[1] - point1->axis[1];
	dz = point2->axis[2] - point1->axis[2];
	return (sqrt(dx * dx + dy * dy + dz * dz));
}

double	magnitude_vector(t_ray_vector *vector)
{
	double	magnitude;

	magnitude = sqrt(pow(vector->axis[0], 2)
			+ pow(vector->axis[1], 2) + pow(vector->axis[2], 2));
	return (magnitude);
}

double	get_t_from_point(t_ray *ray, t_ray_vector *point)
{
	t_ray_vector	diff;
	double			t;

	subtract_vector(point->axis, ray->origin_vect.axis, diff.axis);
	t = magnitude_vector(&diff) / magnitude_vector(&ray->dir_vect);
	return (t);
}
