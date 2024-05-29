#include "rays.h"

# include "mlx.h"
# include "x_mini_struct.h"
# include "x_linear_algebra.h"
# include <math.h>

void	display_error(char *str);

double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
double	is_intersect_cylinder(t_ray *ray, t_cylinder *cylinder,
			t_ray_vector *i);
double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y);
void	invert_vector(double a[], double b[], double r_a[], double r_b[]);
int		has_shadow(t_data *data, void *mesh, t_ray *light_ray);
int		is_equal_vector(double a[], double b[]);
int		is_sphere_surface_between(t_sphere *sphere, t_spotlight *spotlight);

static void	scale_and_add_vectors(t_cam *cam, t_ray *ray, double norm_scale_x,
	double norm_scale_y)
{
	t_matrix_vector	scaled_up;
	t_matrix_vector	scaled_right;
	t_matrix_vector	scaled_forward;
	t_matrix_vector	sum_vect;

	scale_vector(cam->up_vect.axis, norm_scale_y, scaled_up.axis);
	scale_vector(cam->right_vect.axis, norm_scale_x, scaled_right.axis);
	scale_vector(cam->forward_vect.axis, cam->focal_len, scaled_forward.axis);
	add_vector(scaled_up.axis, scaled_right.axis, sum_vect.axis);
	add_vector(sum_vect.axis, scaled_forward.axis, ray->dir_vect.axis);
}

double	normalize_pixel(int screen_size, int pixel, int x_flag)
{
	if (!screen_size)
		return (0.0);
	if (x_flag)
		return (((pixel + 0.5) / screen_size) * 2 - 1);
	return ((1 - 2 * (pixel + 0.5) / screen_size));
}

void	new_ray(t_cam *cam, t_ray *ray, int x, int y)
{
	double	norm_scale_x;
	double	norm_scale_y;

	cast_vector_mat_ray(&cam->origin_vect, &ray->origin_vect);
	norm_scale_y = normalize_pixel(cam->resol[1], y, 0) * cam->scale;
	norm_scale_x = normalize_pixel(cam->resol[0], x, 1) * cam->scale
		* cam->aspect;
	scale_and_add_vectors(cam, ray, norm_scale_x, norm_scale_y);
	normalize_vector(ray->dir_vect.axis);
}

void	put_pxl(t_mlx *mlx, int x, int y, unsigned int color)
{
	const double	inverse_eight = 0.125;
	int				pxl_pos;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl_pos = x * mlx->img.bpp * inverse_eight + y * mlx->img.line_len;
		*(unsigned int *)(mlx->img.img_data + pxl_pos) = color;
	}
}

int	is_behind_cam(double t)
{
	return (t <= 0.0);
}

void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector	scaled_vect;

	scale_vector(ray->dir_vect.axis, t, scaled_vect.axis);
	add_vector(ray->origin_vect.axis, scaled_vect.axis, inter_pt->axis);
}

void	get_local_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt)
{
	t_ray_vector	scaled_vect;

	scale_vector(ray->dir_vect.axis, t, inter_pt->axis);
}

void	put_pxl_alpha(t_mlx *mlx, int x, int y, unsigned int alpha_color, void *img_ptr)
{
	const double	inverse_eight = 0.125;
	int				pxl_pos;

	int bpp, line_len;
	char *img_data = mlx_get_data_addr(img_ptr, &bpp,
		&line_len, &(int){0});

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl_pos = x * mlx->img.bpp * inverse_eight + y * mlx->img.line_len;
		int pxl_pos2 = (x - (WIDTH - 792))  * bpp * inverse_eight + (y - (HEIGHT - 200)) * line_len;		
		if (*(unsigned int *)(img_data + pxl_pos2) != 0x0)		
		{			
			*(unsigned int *)(mlx->img.img_data + pxl_pos) = 
			*(unsigned int *)(img_data + pxl_pos2);
		}
	}
}

void	add_xpm_logo(t_mlx *mlx, int x, int y, void *img_ptr)
{
	const double	inverse_eight = 0.125;
	int				pxl_pos;

	int bpp, line_len;
	char *img_data = mlx_get_data_addr(img_ptr, &bpp,
		&line_len, &(int){0});

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl_pos = x * mlx->img.bpp * inverse_eight + y * mlx->img.line_len;
		int pxl_pos2 = x * bpp * inverse_eight + y * line_len;
		if (*(unsigned int *)(img_data + pxl_pos2) != 0xFF0000)			
		{			
			*(unsigned int *)(mlx->img.img_data + pxl_pos) = 
			*(unsigned int *)(img_data + pxl_pos2);
		}
	}
}

void	add_xpm_sph(t_mlx *mlx, int x, int y, void *img_ptr)
{
	const double	inverse_eight = 0.125;
	int				pxl_pos;

	int bpp, line_len;
	char *img_data = mlx_get_data_addr(img_ptr, &bpp,
		&line_len, &(int){0});

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl_pos = x * mlx->img.bpp * inverse_eight + y * mlx->img.line_len;
		int pxl_pos2 = (x - (WIDTH - 100)) * bpp * inverse_eight + y * line_len;
		if (*(unsigned int *)(img_data + pxl_pos2) != 0xFF0000)			
		{			
			*(unsigned int *)(mlx->img.img_data + pxl_pos) = 
			*(unsigned int *)(img_data + pxl_pos2);
		}
	}
}

void	add_xpm(t_mlx *mlx, int x, int y, void *img)
{
	if (!img)    
		return (display_error("Error loading image\n"));		    
	put_pxl_alpha(mlx, x, y, 0x0, img);
}

void	launch_rays(t_mlx *mlx, t_data *data)
{
	int	x;
	int	y;
	void *img = mlx_xpm_file_to_image(mlx->connect, "lorem.xpm", &(int){0}, &(int){0});
	void *logo = mlx_xpm_file_to_image(mlx->connect, "logo.xpm", &(int){0}, &(int){0});
	void *sph = mlx_xpm_file_to_image(mlx->connect, "sph.xpm", &(int){0}, &(int){0});
	void *cam = mlx_xpm_file_to_image(mlx->connect, "cam.xpm", &(int){0}, &(int){0});
	void *bulb = mlx_xpm_file_to_image(mlx->connect, "bulb.xpm", &(int){0}, &(int){0});
	void *amb = mlx_xpm_file_to_image(mlx->connect, "amb.xpm", &(int){0}, &(int){0});

	y = -1;
	while (++y < data->cam.resol[1])
	{
		x = -1;
		while (++x < data->cam.resol[0])
		{	
			exec_launch_rays(mlx, data, x, y);
			if (x >= 0 && x <= 100 && y >= 0 && y < 100)
				add_xpm_logo(mlx, x, y, logo);
			if (x >= WIDTH - 100 && y >= 0 && y < 100)
			{
				if (data->event.actual_mode == E_CAM)
					add_xpm_sph(mlx, x, y, cam);
				else if (data->event.actual_mode == E_SPOTL)
					add_xpm_sph(mlx, x, y, bulb);
				else if (data->event.actual_mode == E_AMBL)
					add_xpm_sph(mlx, x, y, amb);
				else if (data->event.actual_mode == E_MESH)
					add_xpm_sph(mlx, x, y, sph);			 
			}					
			if (data->event.legend && x >= WIDTH - 792 && y >= HEIGHT - 200)
				add_xpm(mlx, x, y, img);			
		}		
	}
}

