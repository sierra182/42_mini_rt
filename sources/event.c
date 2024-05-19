# include "x_mini_struct.h"
# include "mlx.h"
# include "libft.h"

void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);
void	trsl_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	trsl_about_cam(t_cam *cam, t_matrix_vector *vect, double values[]);

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);
void	rotate_cam(t_cam *cam, double angle, int axe[]);
void	post_init_cam(t_cam *cam);
void	update_cam(t_cam *cam);

void	new_ray(t_cam *cam, t_ray *ray, int x, int y);
void	get_closest_intersection_sp(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_cy(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_pl(t_data *data, t_ray *ray, t_obj *obj);

int	init_data(char *map_path, t_data *data);

static void cam_event_rotate(int keycode, t_cam *cam)
{
    double  r;

    r = 1.0;
    if (keycode == R_LFT)	
		rotate_cam(cam, r, (int []){0, 1, 0});
    else if (keycode == R_RGHT)	
		rotate_cam(cam, -r, (int []){0, 1, 0});
    else if (keycode == R_UP)	
		rotate_cam(cam, r, (int []){1, 0, 0});
    else if (keycode == R_DWN)	
		rotate_cam(cam, -r, (int []){1, 0, 0});
    else if (keycode == S_LFT)	
		rotate_cam(cam, r, (int []){0, 0, 1});
    else if (keycode == S_RGHT)	
		rotate_cam(cam, -r, (int []){0, 0, 1});
}

static void event_rotate(int keycode, t_matrix_vector *vector)
{
    double  r;

    r = 1.0;
    if (keycode == R_LFT)	
		rotate_mesh(vector, r, (int []){1, 0, 0});
    else if (keycode == R_RGHT)	
		rotate_mesh(vector, -r, (int []){1, 0, 0});
    else if (keycode == R_UP)	
		rotate_mesh(vector, r, (int []){0, 1, 0});
    else if (keycode == R_DWN)	
		rotate_mesh(vector, -r, (int []){0, 1, 0});
    else if (keycode == S_LFT)	
		rotate_mesh(vector, r, (int []){0, 0, 1});
    else if (keycode == S_RGHT)	
		rotate_mesh(vector, -r, (int []){0, 0, 1});
}

static void	event_translate(int keycode,
	void (*trsl_mesh)(t_cam *cam, t_matrix_vector *vect, double values[]),
		t_cam *cam, t_matrix_vector *vect)
{
    double t;

    t = 1;
	if (keycode == UP)	
		trsl_mesh(cam, vect, (double []){0.0, t, 0.0});		
	else if (keycode == DWN)
		trsl_mesh(cam, vect, (double []){0.0, -t, 0.0});	
	else if (keycode == LFT)
		trsl_mesh(cam, vect, (double []){t, 0.0, 0.0});	
	else if (keycode == RGHT)
		trsl_mesh(cam, vect, (double []){-t, 0.0, 0.0});
	else if (keycode == FWRD)
		trsl_mesh(cam, vect, (double []){0.0, 0.0, t});
	else if (keycode == BACK)
		trsl_mesh(cam, vect, (double []){0.0, 0.0, -t});
} 	

void	actual_mesh_handle(t_obj *mesh, t_matrix_vector **origin_vect, t_matrix_vector **dir_vect)
{
	static t_obj	actual_mesh;
	
	if (mesh)
	{

		actual_mesh = *mesh;
			// ((t_sphere *) actual_mesh.ref)->color.rgb[0] += 100;
			// if (((t_sphere *) actual_mesh.ref)->color.rgb[0] >= 255)
			// 	((t_sphere *) actual_mesh.ref)->color.rgb[0] = 255;
			
	}
	else 
	{
	
		if ((t_sphere *) actual_mesh.ref)
		{		
			// 	((t_sphere *) actual_mesh.ref)->color.rgb[0] -= 100;
			// if (((t_sphere *) actual_mesh.ref)->color.rgb[0] >= 255)
			// 	((t_sphere *) actual_mesh.ref)->color.rgb[0] = 255;
			if (actual_mesh.type == O_SP)
			{
				*origin_vect = &((t_sphere *) actual_mesh.ref)->origin_vect;
				*dir_vect = NULL;
			}
			if (actual_mesh.type == O_PL)
			{
				*origin_vect = &((t_plane *) actual_mesh.ref)->origin_vect;
				*dir_vect = &((t_plane *) actual_mesh.ref)->norm_vect;
			}
			if (actual_mesh.type == O_CY)
			{
				*origin_vect = &((t_cylinder *) actual_mesh.ref)->origin_vect;
				*dir_vect = &((t_cylinder *) actual_mesh.ref)->axis_vect;
			}
		}
	}
}

void	reset(t_data *data)
{
	t_data		*tmp_data_cpy;
	t_plane 	*tmp_planes;
	t_sphere	*tmp_spheres;
	t_cylinder	*tmp_cylinders;

	t_plane 	*tmp_planes_cpy;
	t_sphere	*tmp_spheres_cpy;
	t_cylinder	*tmp_cylinders_cpy;

	tmp_data_cpy = data->data_cpy;
	tmp_planes = data->planes;
	tmp_spheres = data->spheres;
	tmp_cylinders = data->cylinders;

	tmp_planes_cpy = data->data_cpy->planes;
	tmp_spheres_cpy = data->data_cpy->spheres;
	tmp_cylinders_cpy = data->data_cpy->cylinders;

	*data = *data->data_cpy;

	data->planes = tmp_planes;
	data->spheres = tmp_spheres;
	data->cylinders = tmp_cylinders;

	ft_memcpy(data->planes, tmp_planes_cpy, data->pl_nbr *
		sizeof(t_plane));
	ft_memcpy(data->spheres, tmp_spheres_cpy, data->sp_nbr *
		sizeof(t_sphere));
	ft_memcpy(data->cylinders, tmp_cylinders_cpy, data->cy_nbr *
		sizeof(t_cylinder));
	data->data_cpy = tmp_data_cpy;	
	post_init_cam(&data->cam);
	update_cam(&data->cam);
}

int	key_event(int keycode, void *param)
{
	t_mlx						*mlx;
	t_data						*data;
	static t_event_mesh			mesh_enum;
	t_matrix_vector 			*rotate_vect;
	t_matrix_vector 			*transl_vect;

	mlx = (t_mlx *) ((void **) param)[0];
	data = (t_data *) ((void **) param)[1];
	rotate_vect = NULL;
	transl_vect = NULL;
	data->refresh = 1;
	// printf("keycode: %d\n", keycode);
	if (keycode == RST)	
		reset(data);		
	if (keycode == MESH)	
		mesh_enum = E_MESH;
	if (keycode == CAM)	
		mesh_enum = E_CAM;
	if (keycode == LIGHT)	
		mesh_enum = E_SPOTL;	
	if (mesh_enum == E_CAM)
	{
		event_translate(keycode, trsl_cam, &data->cam, NULL);
		cam_event_rotate(keycode, &data->cam);
	}
	else if (mesh_enum == E_SPOTL)	
		event_translate(keycode, trsl_about_cam, &data->cam, &data->spotlight.origin_vect);
	else 
	{
		actual_mesh_handle(NULL, &transl_vect, &rotate_vect);
		if (transl_vect)
			event_translate(keycode, trsl_about_cam, &data->cam, transl_vect);
		if (rotate_vect)
			event_rotate(keycode, rotate_vect);
	}	
	if (mesh_enum == E_SPOTL)
	{
		data->spotlight.bulb.origin_vect = data->spotlight.origin_vect;
		if (keycode == PLUS && data->spotlight.intensity <= 0.9)
			data->spotlight.intensity += 0.1;
		else if (keycode == MINUS && data->spotlight.intensity >= 0.1)
			data->spotlight.intensity -= 0.1;		
	}
	if (keycode == ESC)
		mlx_loop_end(mlx->connect);
	return (0);
}

void	event_launch_rays(t_data *data, int x, int y)
{
	t_ray	ray;
	t_obj	obj;

	obj.ref = NULL;
	obj.t = 100000000;
	new_ray(&data->cam, &ray, x, y);
	get_closest_intersection_sp(data, &ray, &obj);
	get_closest_intersection_cy(data, &ray, &obj);
	get_closest_intersection_pl(data, &ray, &obj);
	actual_mesh_handle(&obj, NULL, NULL);	
}

int    mouse_event(int button, int x, int y, void *param)
{
    t_data	*data;

    data = (t_data *) param;
	data->refresh = 1;
	if (button == 1)
	{
		event_launch_rays(data, x, y);
		return (0);
	}
    else if (button == 5 && data->cam.fov_deg < 180)
        data->cam.fov_deg++;
    else if (button == 4 && data->cam.fov_deg > 0)
        data->cam.fov_deg--;
    update_cam(&data->cam);	
	return (0);
}
