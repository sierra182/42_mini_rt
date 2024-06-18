#include "se_mini_struct_bonus.h"
#include "x_linear_algebra_bonus.h"

void	calculate_tangent(t_ray_vector *normal, t_ray_vector *T)
{
	T->axis[0] = -normal->axis[2];
	T->axis[1] = 0;
	T->axis[2] = normal->axis[0];

	self_normalize_vector(T->axis);
}

void	calculate_bitangent(t_ray_vector *N, t_ray_vector *T, t_ray_vector *B)
{
	B->axis[0] = N->axis[1] * T->axis[2] - N->axis[2] * T->axis[1];
	B->axis[1] = N->axis[2] * T->axis[0] - N->axis[0] * T->axis[2];
	B->axis[2] = N->axis[0] * T->axis[1] - N->axis[1] * T->axis[0];

	self_normalize_vector(B->axis);
}

void	apply_bump_mapping(t_ray_vector *normal)
{
	t_ray_vector T;
	t_ray_vector B;

	calculate_tangent(normal, &T);
	calculate_bitangent(normal, &T, &B);
	printf("scalar_product(normal, T): %f\n", scalar_product(normal->axis, T.axis));
	printf("scalar_product(normal, B): %f\n", scalar_product(normal->axis, B.axis));
	printf("scalar_product(B, T): %f\n", scalar_product(B.axis, T.axis));
	
}