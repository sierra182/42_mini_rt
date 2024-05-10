#include "x_mini_struct.h"
#include "math.h"
double	scalar_product(double a[], double b[]);

void    vecop_vect_mat_minus_ray(t_matrix_vector *m, t_ray_vector *r, t_ray_vector *res)
{
    int i;

    i = -1;
    while (++i < AXIS)
        res->axis[i] = m->axis[i] - r->axis[i];
}

void    is_intersect_plane(t_ray *ray, t_plane *plane, double *t2)
{
    t_ray_vector a;
    double num;
    double den;

    vecop_vect_mat_minus_ray(&plane->origin_vect, &ray->origin_vect, &a);
    num = scalar_product(a.axis, plane->norm_vect.axis);
    den = scalar_product(ray->dir_vect.axis, plane->norm_vect.axis);
    if (den)
        *t2 = num / den;
    else
        den = 0;
    // printf("truc: %f\n", *t2);
}

void    is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder, double *t2)
{

    // printf("is_intersect_cylinder\n");
}