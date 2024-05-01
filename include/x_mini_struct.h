#ifndef X_MINI_STRUCT_H
# define X_MINI_STRUCT_H

# define WIDTH 600
# define HEIGHT 500
# define AXIS 3

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

typedef struct s_vector
{
	double	axis[AXIS];
}	t_vector;

typedef struct s_ray
{
	t_vector	origin_vect;
	t_vector	dir_vect;
}	t_ray;

typedef struct s_cam
{
	double		fov;
	double		focal_len;
	double		scale;
	double		aspect;
	double		resol[2];	
	t_vector	origin_vect;
	t_vector	up_vect;
	t_vector	forward_vect;
	t_vector	right_vect;
}	t_cam;

typedef struct	s_color
{
	int	rgb[3];
}	t_color;

typedef struct s_sphere
{
	t_vector	origin_vect;
	double		diameter;
	t_color		color;
}	t_sphere;

typedef struct s_cylinder
{
	t_color		color;
}	t_cylinder;

typedef struct s_plane
{
	t_color		color;
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
}	t_data;

typedef struct s_exit
{
	t_mlx	*mlx;
}	t_exit;

typedef enum e_event
{
	ESC = 65307
}	t_enum_event;

typedef enum e_exit
{
	STT,
	MLX,
	END
}	t_enum_exit;

#endif