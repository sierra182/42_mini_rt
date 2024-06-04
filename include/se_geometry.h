#ifndef X_GEOMETRY_H
# define X_GEOMETRY_H

typedef enum e_cyl_or_discs
{
	cylinder,
	discs
}	t_cyl_or_discs;

typedef struct s_sphere
{
	t_matrix_vector	origin_vect;
	double			diameter;
	double			radius;
	double			square_radius;
	t_color			color;
	int				which_t;
	double			t1;
	double			t2;
}	t_sphere;

typedef struct s_cylinder
{
	double			proj;
	t_matrix_vector	origin_vect;
	t_matrix_vector	axis_vect;
	double			diameter;
	double			radius;
	double			square_radius;
	double			height;
	t_color			color;
	int				which_t;	
	t_cyl_or_discs	cyl_or_discs;
	t_ray_vector	intersec_point;
	t_ray_vector	origin_proj;
	double			t1;
	double			t2;
}	t_cylinder;

typedef struct s_plane
{
	t_matrix_vector	origin_vect;
	t_matrix_vector	norm_vect;
	t_color			color;
}	t_plane;

#endif