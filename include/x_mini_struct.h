#ifndef X_MINI_STRUCT_H
# define X_MINI_STRUCT_H

# define WIDTH 600
# define HEIGHT 500
# define AXIS 3
# define MTX 4 
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
	int	rgb[3];
}	t_color;

typedef struct	s_spotlight
{
	double			intensity;
	t_matrix_vector	origin_vect;
}	t_spotlight;

typedef struct s_sphere
{
	t_matrix_vector	origin_vect;
	double			diameter;
	double			square_radius;
	t_color			color;
}	t_sphere;

typedef struct s_cylinder
{
	t_matrix_vector	origin_vect;
	t_matrix_vector	axis_vect;
	float			diameter;
	float			height;
	t_color			color;
}	t_cylinder;

typedef struct s_plane
{
	t_matrix_vector	origin_vect;
	t_matrix_vector	norm_vect;
	t_color			color;
}	t_plane;

typedef struct s_data
{
	int			sp_nbr;
	int			pl_nbr;
	int			cy_nbr;
	t_cam		cam;
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_plane		*planes;
	t_spotlight	spotlight;
}	t_data;

typedef enum e_event
{
	ESC = 65307,
	UP = 65362,
	DWN = 65364,
	LFT = 65361,
	RGHT = 65363,
	FWRD = 65436,
	BACK = 65438,
	R_UP = 65431,
	R_DWN = 65434,
	R_LFT = 65437,
	R_RGHT = 65432,
	S_LFT = 65433,
	S_RGHT = 65435,
	MESH = 111
}	t_enum_event;

typedef enum e_event_mesh
{		
	CAM,
	SPH,
	SPOTL,
	MESH_END
}	t_enum_event_mesh;

typedef struct s_exit
{
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_plane		*planes;
	t_mlx		*mlx;
}	t_exit;

typedef enum e_exit
{
	STT,
	MLX,
	SP,
	CY,
	PL,
	END
}	t_enum_exit;

#endif