#include "x_mini_struct.h"
#include "math.h"
void	subtract_vector(t_ray_vector *a, t_matrix_vector *b, t_ray_vector *subt_vect);
void	subtract_torvec(t_matrix_vector *b, t_ray_vector *a, t_ray_vector *subt_vect);
double	product_scalar_matrix(t_ray_vector *d, t_matrix_vector *n);
double	product_scalar(t_ray_vector *a, t_ray_vector *b);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
void	scale_matrix_vector(t_matrix_vector *vect, double scaler, t_matrix_vector *scaled_vect);
void	add_matrix_to_ray_vector(t_matrix_vector *a, t_matrix_vector *b, t_ray_vector *sum_vect);
void	add_matrix_vector(t_matrix_vector *a, t_matrix_vector *b, t_matrix_vector *sum_vect);
void	scale_ray_vector(t_ray_vector *vect, double scaler, t_ray_vector *scaled_vect);
void	add_ray_vector(t_ray_vector *a, t_ray_vector *b, t_ray_vector *sum_vect);
void	subtract_vecvec(t_ray_vector *a, t_ray_vector *b, t_ray_vector *subt_vect);

void    vecop_vect_mat_minus_ray(t_matrix_vector *m, t_ray_vector *r, t_ray_vector *res)
{
    int i;

    i = -1;
    while (++i < AXIS)
        res->axis[i] = m->axis[i] - r->axis[i];
}

void	print_vector(t_matrix_vector vec)
{
	printf("%f, %f, %f\n", vec.axis[0], vec.axis[1], vec.axis[2]);
}

double    is_intersect_plane(t_ray *ray, t_plane *plane, t_ray_vector *i_point)
{
	double t;
    t_ray_vector a;
    double num;
    double den;

    vecop_vect_mat_minus_ray(&plane->origin_vect, &ray->origin_vect, &a);
    num = product_scalar_matrix(&a, &plane->norm_vect);
    den = product_scalar_matrix(&ray->dir_vect, &plane->norm_vect);
    if (den)
	{
		t = num / den;
		if (t >= 0.0)
		{
            // Calculate intersection point coordinates
            scale_ray_vector(&ray->dir_vect, t, i_point);
            add_ray_vector(&ray->origin_vect, i_point, i_point);
			// printf("interesct! %f, %f, %f\n", i_point->axis[0], i_point->axis[1], i_point->axis[2]);
            return 1; // Intersection with the plane
        }
	}
	return (0);
}

double distance_between_points(t_ray_vector *point1, t_matrix_vector *point2) {
    double dx = point2->axis[0] - point1->axis[0];
    double dy = point2->axis[1] - point1->axis[1];
    double dz = point2->axis[2] - point1->axis[2];
    return sqrt(dx * dx + dy * dy + dz * dz);
}



int	intersect_disc_plans(t_ray *ray, t_cylinder *cylinder, t_ray_vector	*i_point)
{
	t_plane plane_1;
	t_plane plane_2;
	t_matrix_vector scaled_v;

	plane_2.origin_vect.axis[0] = 0;
	plane_2.origin_vect.axis[1] = 0;
	plane_2.origin_vect.axis[2] = 0;
	plane_1.origin_vect.axis[0] = 0;
	plane_1.origin_vect.axis[1] = 0;
	plane_1.origin_vect.axis[2] = 0;
	
	
	
	plane_1.norm_vect = cylinder->axis_vect;
    plane_2.norm_vect = cylinder->axis_vect;


	scale_matrix_vector(&cylinder->axis_vect, cylinder->height / 2, &scaled_v);
	add_matrix_vector(&scaled_v, &cylinder->origin_vect, &plane_1.origin_vect);


	scale_matrix_vector(&cylinder->axis_vect, - cylinder->height / 2, &scaled_v);
	add_matrix_vector(&scaled_v, &cylinder->origin_vect, &plane_2.origin_vect);


	// print_vector(plane_1.norm_vect);

	if (is_intersect_plane(ray, &plane_1, i_point) || is_intersect_plane(ray, &plane_2, i_point))
	{

		if (distance_between_points(i_point, &plane_1.origin_vect) > cylinder->radius && distance_between_points(i_point, &plane_2.origin_vect) > cylinder->radius)
		{

			return (0);
		}
		return (1);
	}
	return (0);
}


double magnitude_vector(t_ray_vector *vector) {
    // Calculer la magnitude du vecteur en utilisant la formule mathématique sqrt(x^2 + y^2 + z^2)
    double magnitude = sqrt(pow(vector->axis[0], 2) + pow(vector->axis[1], 2) + pow(vector->axis[2], 2));
    return magnitude;
}


double get_t_from_point(t_ray *ray, t_ray_vector *point) {
    // Calculer le vecteur entre l'origine du rayon et le point donné
    t_ray_vector diff;
    subtract_vecvec(point, &ray->origin_vect, &diff);

    // Calculer le paramètre t en divisant la magnitude du vecteur de différence
    // par la magnitude du vecteur de direction du rayon
    double t = magnitude_vector(&diff) / magnitude_vector(&ray->dir_vect);
    return t;
}


double	is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_ray_vector	SR;
	double			a;
	double			b;
	double			c;	
	double			discrim;
	double			t1;
	t_ray_vector	i_point;

	subtract_vector(&ray->origin_vect, &cylinder->origin_vect, &SR);

	a = product_scalar(&ray->dir_vect, &ray->dir_vect) - pow(product_scalar_matrix(&ray->dir_vect, &cylinder->axis_vect), 2);

    b = 2 * (product_scalar(&ray->dir_vect, &SR) - product_scalar_matrix(&ray->dir_vect, &cylinder->axis_vect) * product_scalar_matrix(&SR, &cylinder->axis_vect));
    c = product_scalar(&SR, &SR) - pow(product_scalar_matrix(&SR, &cylinder->axis_vect), 2) - cylinder->square_radius;

	discrim = b * b - 4 * a * c;
	

	t1 = (-b - sqrt(discrim)) / (2*a); // t2 = (-b + sqrt(discrim)) / (2*a) 	 
	
	// get intersection point coordinates
	get_intersect_point(ray, t1, &i_point);
	// project IP on cylinder axis
	double proj = product_scalar_matrix(&i_point, &cylinder->axis_vect);
	
	// check if projection is within cylinder height

	if (intersect_disc_plans(ray, cylinder, &i_point))
	{
		// printf("intersect\n");
		return (get_t_from_point(ray, &i_point));
	}

	if (proj < 0 || proj > cylinder->height / 2)
		return (0.0);


	if (discrim < 0)
	    return (0.0);
	return (t1);
}
