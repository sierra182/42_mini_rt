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

typedef struct s_get_color_params
{
	t_data			*data;
	t_ray			*ray;
	double			t;
	t_obj			*mesh;
	t_color			*color;
	t_ray_vector	*normal;
}	t_get_color_params;

typedef struct s_add_lightening_params
{
	t_ray			*light_ray;
	t_ray_vector	*normal;
	t_spotlight		*spotlight;
	t_color			*color;
	t_color			*res_color;
	double			*light_attenuat;
	double			*light_coef;
}	t_add_lightening_params;

typedef struct s_get_pixel_color_2_params
{
	t_data	*data;
	t_ray	*ray;
	t_obj	*obj;
	int		*rgb;
	double	*inter_bulb;
	t_color	*color;
}	t_get_pixel_color_2_params;

typedef struct s_get_cyl_col_cyl_2_params
{
	t_get_color_params	*params;
	t_ray_vector		*normal;
	t_ray				*light_ray;
	t_color				*ambiantly_color;
	t_color				*spotlighty_color;
}	t_get_cyl_col_cyl_2_params;

typedef struct s_get_cyl_col_cyl_0_params
{
	t_get_color_params	*params;
	t_ray_vector		*normal;
	t_ray				*light_ray;
	t_color				*ambiantly_color;
	t_color				*spotlighty_color;
}	t_get_cyl_col_cyl_0_params;

typedef struct s_get_cylinder_color_discs_params
{
	t_get_color_params	*params;
	t_ray_vector		*normal;
	t_ray				*light_ray;
	double				light_attenuat;
	double				light_coef;
}	t_get_cylinder_color_discs_params;

typedef struct s_add_shad_and_light_params
{
	t_get_color_params	*params;
	t_ray_vector		*normal;
	t_ray				*light_ray;
	t_color				*ambiantly_color;
	t_color				*spotlighty_color;

}	t_add_shad_and_light_params;

typedef struct s_calc_spotlight_effect_params
{
	t_get_color_params	*params;
	t_color				*mesh_color;
	t_ray_vector		*normal;
	t_color				*spotlighty_color;
	t_ray_pack			*light_ray;
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

#endif