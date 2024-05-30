#ifndef X_LIGHTING_H
# define X_LIGHTING_H

typedef struct	s_spotlight
{
	double			intensity;
	t_matrix_vector	origin_vect;
	t_sphere		bulb;
}	t_spotlight;

typedef struct	s_ambiant_light
{
	double			intensity;
	t_color			color;
}	t_ambiant_light;


#endif