#ifndef RAYS_H
# define RAYS_H

# include "mlx.h"
# include "x_mini_struct.h"
# include <math.h>

void	cast_vector(t_matrix_vector *matrix_vect, t_ray_vector *ray_vect);
void	scale_matrix_vector(t_matrix_vector *vect, double scaler, t_matrix_vector *scaled_vect);
void	scale_ray_vector(t_ray_vector *vect, double scaler, t_ray_vector *scaled_vect);
void	add_matrix_vector(t_matrix_vector *a, t_matrix_vector *b, t_matrix_vector *sum_vect);
void	add_matrix_to_ray_vector(t_matrix_vector *a, t_matrix_vector *b, t_ray_vector *sum_vect);
void	add_ray_vector(t_ray_vector *a, t_ray_vector *b, t_ray_vector *sum_vect);
void	subtract_vector(t_ray_vector *a, t_matrix_vector *b, t_ray_vector *subt_vect);
void	subtract_color_vector(t_ray_vector *a, t_matrix_vector *b, t_color *subt_vect);
double	product_scalar(t_ray_vector *a, t_ray_vector *b);
void	normalize_vector(t_ray_vector *vector);
void	cast_vector_to_color(t_ray_vector *ray_vect, t_color *color);

#endif