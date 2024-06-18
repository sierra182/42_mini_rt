#ifndef SE_FUNCS_PARAMS_BONUS_H
# define SE_FUNCS_PARAMS_BONUS_H

typedef struct s_intersection_params
{
	t_ray			ray;
	void			*objects;
	int				obj_nbr;
	double			(*intersect_func)(t_ray *, void *, t_ray_vector *);
	t_obj			*obj;
	int				obj_type;
	t_ray_vector	*i;
}	t_intersection_params;

typedef struct s_get_pixel_color_2_params
{
	t_data	*data;
	t_ray	*ray;
	t_obj	*obj;
	int		*rgb;
	double	*inter_bulb;
	t_color	*color;
}	t_get_pixel_color_2_params;

typedef struct s_get_color_params
{
	t_data			*data;
	t_ray			*ray;
	double			t;
	t_obj			*mesh;
	t_color			*color;
	t_ray_vector	*normal;//!
}	t_get_color_params;

typedef struct s_calc_spotlight_effect_params
{
	t_get_color_params	*params;
	t_color				*mesh_color;
	t_ray_vector		*normal;
	t_color				*spotlighty_color;
	t_ray_pack			*light_ray;
	t_spotlight			*spotlight;
}	t_calc_spotlight_effect_params;

typedef struct s_reset_tmps
{
	t_plane		*planes;
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_spotlight	*spotlights;
	t_data		*data_cpy;
	t_plane		*planes_cpy;
	t_sphere	*spheres_cpy;
	t_cylinder	*cylinders_cpy;
	t_spotlight	*spotlights_cpy;
}	t_reset_tmps;

typedef struct s_calculate_bump_derivatives_params
{
	double u;
	double v;
	double *du;
	double *dv;
	double **bump_map;
}	t_calculate_bump_derivatives_params;

typedef struct	s_fill_bump_map
{
	int shades_nbr;
	t_data *data;
	int fd;
	int i;
}	t_fill_bump_map;

#endif