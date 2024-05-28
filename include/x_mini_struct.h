#ifndef X_MINI_STRUCT_H
# define X_MINI_STRUCT_H

# define WIDTH 800
# define HEIGHT 600
# define AXIS 3
# define MTX 4 
# define BIG_VALUE 100000000
# include <stdio.h>

typedef	struct s_img
{
	void	*img_ptr;
	char	*img_data;
	int		line_len;
	int		bpp;
}	t_img;

typedef struct s_mlx
{
	void	*connect;
	void	*window;
	t_img	img;
}	t_mlx;

typedef struct s_ray_vector
{
	double	axis[AXIS];
}	t_ray_vector;

typedef struct s_matrix_vector
{
	double	axis[MTX];
}	t_matrix_vector;

typedef struct s_ray
{
	t_ray_vector	origin_vect;
	t_ray_vector	dir_vect;
}	t_ray;

typedef struct s_cam
{
	double			fov_deg;
	double			fov_rad;
	double			focal_len;
	double			scale;
	double			aspect;
	double			resol[2];
	t_matrix_vector	*cam_matrix[MTX];
	t_matrix_vector	right_vect;
	t_matrix_vector	up_vect;
	t_matrix_vector	forward_vect;
	t_matrix_vector	origin_vect;
}	t_cam;

typedef struct	s_color
{
	int	rgb[AXIS];
}	t_color;

typedef struct s_sphere
{
	t_matrix_vector	origin_vect;
	double			diameter;
	double			square_radius;
	t_color			color;
	int				which_t;
	double			t1;
	double			t2;
}	t_sphere;

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

typedef enum e_cyl_or_discs
{
	cylinder,
	discs
} t_cyl_or_discs;

typedef struct s_cylinder
{
	double			proj;
	t_matrix_vector	origin_vect;
	t_matrix_vector	axis_vect;
	double			diameter;
	double			square_radius;
	double			radius;
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

typedef enum e_event_mesh
{		
	E_CAM,	
	E_SPOTL,
	E_AMBL,
	E_MESH
}	t_event_mesh;

typedef enum e_obj_type
{
	O_SP,
	O_CY,
	O_PL
} t_obj_type;

typedef	struct s_obj_intersect
{
	double			t;
	enum e_obj_type	type;
	void			*ref;
}	t_obj;

typedef struct s_event
{
	int				ctrl_ispressed;
	int				legend;
	t_event_mesh	type_mesh;
	t_obj			actual_mesh;
	t_color			color_sav;
}	t_event;

typedef struct s_data
{
	int				refresh;
	int				sp_nbr;
	int				pl_nbr;
	int				cy_nbr;
	t_event			event;
	t_cam			cam;
	t_sphere		*spheres;
	t_cylinder		*cylinders;
	t_plane			*planes;
	t_spotlight		spotlight;
	t_ambiant_light	ambiant_light;
	struct s_data	*data_cpy;
}	t_data;

typedef enum e_event
{

	ESC = 65307,
	RST = 114,
	RST_CM = 65437,
	UP = 65434,
	DWN = 65435,
	LFT = 65363,
	RGHT = 65361,
	FWRD = 65362,
	BACK = 65364,
	R_UP = 65431,
	R_DWN = 65433,
	R_LFT = 65430,
	R_RGHT = 65432,
	S_LFT = 65436,
	S_RGHT = 65429,
	PLUS = 65451,
	MINUS = 65453,
	CAM = 99,
	AMBL = 97,
	LIGHT = 108, 
	MESH = 111,
	CTRL = 65507,
	CTRL_2 = 65508,
	MAKE_RT_FILE = 109
}	t_enum_event;


typedef struct s_exit
{
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_plane		*planes;
	t_mlx		*mlx;
	t_data		*data_cpy;
}	t_exit;

typedef enum e_exit
{
	STT,
	MLX,
	SP,
	CY,
	PL,
	DATA,
	END
}	t_enum_exit;

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
	t_data	*data;
	t_ray	*ray;
	double	t;
	void	*mesh;
	t_color *color;
}	t_get_color_params;

typedef struct s_add_lightening_params
{
	t_ray 			*light_ray;
	t_ray_vector	*normal;
	t_spotlight		*spotlight;
	t_color			*color;
	t_color			*res_color;
	double			*light_attenuat;
	double 			*light_coef;
}	t_add_lightening_params;

typedef struct s_reset_tmps
{
	t_plane 	*planes;
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_data		*data_cpy;
	t_plane 	*planes_cpy;
	t_sphere	*spheres_cpy;
	t_cylinder	*cylinders_cpy;
}	t_reset_tmps;

#endif