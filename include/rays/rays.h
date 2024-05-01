#ifndef RAYS_H
# define RAYS_H

# include "mlx.h"
# include "x_mini_struct.h"

void	scale_vector(t_vector *vect, double scaler, t_vector *scaled_vect);
void	add_vector(t_vector *a, t_vector *b, t_vector *sum_vect);
void	normalize_vector(t_vector *vector);

#endif