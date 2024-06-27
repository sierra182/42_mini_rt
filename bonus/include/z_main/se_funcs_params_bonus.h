/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_funcs_params_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:39:46 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:39:47 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SE_FUNCS_PARAMS_BONUS_H
# define SE_FUNCS_PARAMS_BONUS_H

# define TRI_E 1e-6
# define THR 4
# define THR_SQRT 2
# define THR_INV_SQRT 0.5

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
	t_obj			*mesh;
	t_color			*color;
	t_ray_vector	*normal;
	t_ray_pack		*light_ray;
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
	double		u;
	double		v;
	double		*du;
	double		*dv;
	double		**bump_map;
	t_sphere	*sphere;
}	t_calculate_bump_derivatives_params;

typedef struct s_fill_bump_map
{
	int		shades_nbr;
	int		char_pp;
	t_data	*data;
	int		fd;
	int		i;
}	t_fill_bump_map;

typedef struct s_handle_line_params
{
	t_data	*data;
	char	*str;
	int		*j;
	int		i;
	int		shades_nbr;
	int		char_pp;
	int		*l;
}	t_handle_line_params;

typedef struct s_antia
{
	double	alia;
	double	inv_alia;
	double	ay;
	double	ax;
	double	ax_cpy;
	int		i;
	int		j;
	int		k;
	t_ray	ray;
	t_obj	obj;
	t_color	colors[16];
	t_color	average_color;
}	t_antia;

typedef struct s_is_intersect_triangle
{
	t_triangle		*triangle;
	t_ray_vector	p;
	t_ray_vector	t_vect;
	t_ray_vector	q;
	double			det;
	double			inv_det;
	double			u;
	double			v;
	double			t;
}	t_tri;

typedef struct s_uv_to_texture_coordinates_params
{
	t_sphere	*sphere;
	double		u;
	double		v;
	int			*x;
	int			*y;
}	t_uv_to_texture_params;

typedef struct s_reflexion
{
	t_ray			reflex_ray;
	t_color			reflex_color;
	t_ray_vector	normal;
	t_ray_pack		light_ray;
	int				deep;
	double			reflex_coef;
	double			color_coef;	
}	t_reflexion;

typedef struct s_multy_threads
{
	t_mlx	mlx;
	t_data	*data;
	int		x_stt;
	int		x_end;
	int		y_stt;
	int		y_end;
}	t_multy_threads;

#endif