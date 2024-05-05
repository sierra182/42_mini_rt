#include "x_mini_struct.h"
#include "math.h"
void	subtract_vector(t_ray_vector *a, t_matrix_vector *b, t_ray_vector *subt_vect);
void	subtract_torvec(t_matrix_vector *b, t_ray_vector *a, t_ray_vector *subt_vect);
double	product_scalar_matrix(t_ray_vector *d, t_matrix_vector *n);
double	product_scalar(t_ray_vector *a, t_ray_vector *b);


void    vecop_vect_mat_minus_ray(t_matrix_vector *m, t_ray_vector *r, t_ray_vector *res)
{
    int i;

    i = -1;
    while (++i < AXIS)
        res->axis[i] = m->axis[i] - r->axis[i];
}

// void	vecop_scal_ray_div_ray(t_ray_vector *r1, t_ray_vector *r2, double *res)
// {
//     double scalar;	
//     int	i;

//     scalar = 0.0;
//     i = -1;
//     while (++i < AXIS)
//     {
//         // printf("r1->axis[%i], r2->axis[%i]: %f, %f\n", i, i, r1->axis[i], r2->axis[i]);
//         if (r2->axis[i])
//             *res += r1->axis[i] / r2->axis[i];
//         else
//             *res = 0;
//         // printf("res : %f\n", *res);
//     }
// }
void    is_intersect_plane(t_ray *ray, t_plane *plane, double *t2)
{
    t_ray_vector a;
    double num;
    double den;

    vecop_vect_mat_minus_ray(&plane->origin_vect, &ray->origin_vect, &a);
    num = product_scalar_matrix(&a, &plane->norm_vect);
    den = product_scalar_matrix(&ray->dir_vect, &plane->norm_vect);
    *t2 = num / den;
    // printf("truc: %f\n", *t2);
}