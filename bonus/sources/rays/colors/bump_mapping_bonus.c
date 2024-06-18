#include "se_mini_struct_bonus.h"
#include "x_linear_algebra_bonus.h"
double get_bump_coef(double **bump_map, double u, double v);
#include <stdio.h>

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

void calculate_bump_derivatives(double u, double v, double *du, double *dv, double **bump_map)
{
	double delta_u = 1.0 / 512.0;
	double delta_v = 1.0 / 512.0;

	double bump_coef = get_bump_coef(bump_map, u, v);
	double bump_coef_u = get_bump_coef(bump_map, u + delta_u, v);  // Valeur à (u + Δu, v)
	double bump_coef_v = get_bump_coef(bump_map, u, v + delta_v);  // Valeur à (u, v + Δv)

	// Calcul des dérivées partielles par différences finies
	*du = (bump_coef_u - bump_coef) / delta_u;
	*dv = (bump_coef_v - bump_coef) / delta_v;

	// printf("bump_coef at (%f, %f): %f\n", u, v, bump_coef);
    // printf("bump_coef at (%f, %f): %f\n", u + delta_u, v, bump_coef_u);
    // printf("bump_coef at (%f, %f): %f\n", u, v + delta_v, bump_coef_v);
    // printf("Partial derivative du: %f\n", *du);
    // printf("Partial derivative dv: %f\n", *dv);
}

void	apply_bump_mapping(t_ray_vector *normal, double u, double v, double **bump_map)
{
	t_ray_vector T;
	t_ray_vector B;
	double du;
	double dv;

	calculate_tangent(normal, &T);
	calculate_bitangent(normal, &T, &B);
	calculate_bump_derivatives(u, v, &du, &dv, bump_map);

	// printf("Tangent vector: (%f, %f, %f)\n", T.axis[0], T.axis[1], T.axis[2]);
    // printf("Bitangent vector: (%f, %f, %f)\n", B.axis[0], B.axis[1], B.axis[2]);
    // printf("du: %f, dv: %f\n", du, dv);
	// printf("scalar_product(normal, T): %f\n", scalar_product(normal->axis, T.axis));
	// printf("scalar_product(normal, B): %f\n", scalar_product(normal->axis, B.axis));
	// printf("scalar_product(B, T): %f\n", scalar_product(B.axis, T.axis));
	
	t_ray_vector N_prime;
    double scale = 0.001;  // Example scale factor for bump mapping

    N_prime.axis[0] = normal->axis[0] + scale * (du * T.axis[0] + dv * B.axis[0]);
    N_prime.axis[1] = normal->axis[1] + scale * (du * T.axis[1] + dv * B.axis[1]);
    N_prime.axis[2] = normal->axis[2] + scale * (du * T.axis[2] + dv * B.axis[2]);

    self_normalize_vector(N_prime.axis);
	*normal = N_prime;
    // Debug print for perturbed normal
    // printf("Original normal: (%f, %f, %f)\n", normal->axis[0], normal->axis[1], normal->axis[2]);
    // printf("Perturbed normal: (%f, %f, %f)\n", N_prime.axis[0], N_prime.axis[1], N_prime.axis[2]);
}