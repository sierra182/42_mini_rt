#ifndef RAYS_H
# define RAYS_H

# include "mlx.h"
# include "x_mini_struct.h"
# include <math.h>

void	cast_vector_mat_ray(t_matrix_vector *matrix_vect, t_ray_vector *ray_vect);
// void	scale_matrix_vector(t_matrix_vector *vect, double scaler, t_matrix_vector *scaled_vect);
// void	scale_ray_vector(t_ray_vector *vect, double scaler, t_ray_vector *scaled_vect);

void    add_vector(double a[], double b[], double sum_vect[]);
void	add_color(t_color *a, t_color *b, t_color *sum_color);
void	subtract_vector(double a[], double b[], double subt_vect[]);
void	subtract_color(t_color *a, t_color *b, t_color *subt_color);
void	scale_vector(double vect[], double scaler, double scaled_vect[]);
void	scale_color(t_color *color, double scaler, t_color *scaled_color);
double	scalar_product(double a[], double b[]);
void	normalize_vector(double vector[]);

double	normalize_zero_one(double scalar_product);

// void	add_matrix_vector(t_matrix_vector *a, t_matrix_vector *b, t_matrix_vector *sum_vect);

// void	add_matrix_to_ray_vector(t_matrix_vector *a, t_matrix_vector *b, t_ray_vector *sum_vect);
// void	add_ray_vector(t_ray_vector *a, t_ray_vector *b, t_ray_vector *sum_vect);

// void	subtract_vector(t_ray_vector *a, t_matrix_vector *b, t_ray_vector *subt_vect);
// void	subtract_color_vector(t_ray_vector *a, t_matrix_vector *b, t_color *subt_vect);
// double	scalar_product(t_ray_vector *a, t_ray_vector *b);

// void	cast_vector_ray_to_color(t_ray_vector *ray_vect, t_color *color);
// void	cast_vector_to_color(t_ray_vector *ray_vect, t_color *color);
// void	scale_color(t_color *vect, double scaler, t_ray_vector *scaled_vect);


double    is_intersect_plane(t_ray *ray, t_plane *plane, double *t);
double    is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder, double *t2);
// void	subtract_torvec(t_matrix_vector *b, t_ray_vector *a, t_ray_vector *subt_vect);
// void	subtract_color_color(t_color *a, t_color *b, t_color *subt_color);

#endif