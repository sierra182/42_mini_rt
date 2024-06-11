#ifndef SE_RAY_VECTOR_H
# define SE_RAY_VECTOR_H

typedef struct s_ray_vector
{
	double	axis[AXIS];
}	t_ray_vector;

typedef struct s_matrix_vector
{
	double	axis[MTX];
}	t_matrix_vector;

typedef struct s_ray
{
	t_ray_vector	origin_vect;
	t_ray_vector	dir_vect;
}	t_ray;

typedef struct s_ray_pack
{
	t_ray	ray;
	t_ray	ray_norm;
	double	magnitude;
}	t_ray_pack;

#endif