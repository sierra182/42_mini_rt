#include "x_mini_struct.h"
#include "math.h"
void	subtract_vector(t_ray_vector *a, t_matrix_vector *b, t_ray_vector *subt_vect);
void	subtract_torvec(t_matrix_vector *b, t_ray_vector *a, t_ray_vector *subt_vect);
double	product_scalar_matrix(t_ray_vector *d, t_matrix_vector *n);
double	product_scalar(t_ray_vector *a, t_ray_vector *b);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
void	scale_matrix_vector(t_matrix_vector *vect, double scaler, t_matrix_vector *scaled_vect);
void	add_matrix_to_ray_vector(t_matrix_vector *a, t_matrix_vector *b, t_ray_vector *sum_vect);


void    vecop_vect_mat_minus_ray(t_matrix_vector *m, t_ray_vector *r, t_ray_vector *res)
{
    int i;

    i = -1;
    while (++i < AXIS)
        res->axis[i] = m->axis[i] - r->axis[i];
}

double    is_intersect_plane(t_ray *ray, t_plane *plane)
{
    t_ray_vector a;
    double num;
    double den;

    vecop_vect_mat_minus_ray(&plane->origin_vect, &ray->origin_vect, &a);
    num = product_scalar_matrix(&a, &plane->norm_vect);
    den = product_scalar_matrix(&ray->dir_vect, &plane->norm_vect);
    if (den)
        return (num / den);
    else
        return (0);
}

double	is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_ray_vector	SR;
	double			a;
	double			b;
	double			c;	
	double			discrim;
	double			t1;

	subtract_vector(&ray->origin_vect, &cylinder->origin_vect, &SR);

	a = product_scalar(&ray->dir_vect, &ray->dir_vect) - pow(product_scalar_matrix(&ray->dir_vect, &cylinder->axis_vect), 2);

    b = 2 * (product_scalar(&ray->dir_vect, &SR) - product_scalar_matrix(&ray->dir_vect, &cylinder->axis_vect) * product_scalar_matrix(&SR, &cylinder->axis_vect));
    c = product_scalar(&SR, &SR) - pow(product_scalar_matrix(&SR, &cylinder->axis_vect), 2) - cylinder->square_radius;

	discrim = b * b - 4 * a * c;
	
	if (discrim < 0)
	    return (0.0);

	t1 = (-b - sqrt(discrim)) / (2*a); // t2 = (-b + sqrt(discrim)) / (2*a) 	 
	
	t_ray_vector	i_point;
	// get intersection point coordinates
	get_intersect_point(ray, t1, &i_point);
	// project IP on cylinder axis
	double proj = product_scalar_matrix(&i_point, &cylinder->axis_vect);
	
	// check if projection is within cylinder height
	if (proj < 0 || proj > cylinder->height / 2)
		return (0.0);


	return (t1);
}