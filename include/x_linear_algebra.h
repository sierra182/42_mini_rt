#ifndef X_LINEAR_ALGEBRA_H
# define X_LINEAR_ALGEBRA_H
# include "x_mini_struct.h"

void	normalize_vector(double vector[]);
void	add_color(t_color *a, t_color *b, t_color *sum_color);
void	subtract_color(t_color *a, t_color *b, t_color *subt_color);
void	scale_color(t_color *color, double scaler, t_color *scaled_color);
void	add_vector(double a[], double b[], double sum_vect[]);
void	subtract_vector(double a[], double b[], double subt_vect[]);
void	scale_vector(double vect[], double scaler, double scaled_vect[]);
double	scalar_product(double a[], double b[]);
void	cross_product(t_matrix_vector *a, t_matrix_vector *b,
			t_matrix_vector *product_vect);
void	cast_vector_mat_ray(t_matrix_vector *matrix_vect,
			t_ray_vector *ray_vect);
int		are_collinear_vectors(t_matrix_vector *cross_prdct, double precision);
int		are_collinear_vectors_diff_origin(double a[], double b[]);
void	normalize_zero_one(double *scalar_product);
void	normalize_vector(double vector[]);
double	get_vector_magnitude(double vector[]);
double	*symmetrize_vector(double vect[]);
void	invert_vector(double ori[], double dir[], double inv_ori[],
			double inv_dir[]);
int		is_equal_vector(double a[], double b[]);
void	get_average_color(t_color *a, t_color *b, t_color *average);
void	limit_to_255(t_color *color);
int		get_color(unsigned char r, unsigned char g, unsigned char b);

#endif