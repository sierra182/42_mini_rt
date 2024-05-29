# include "x_mini_struct.h"
# include "mlx.h"
# include "libft.h"

void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);
void	trsl_cam(t_cam *cam, t_matrix_vector *vect, double values[]);
void	trsl_about_cam(t_cam *cam, t_matrix_vector *vect, double values[]);

void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[]);
void	rotate_cam(t_cam *cam, double angle, int axe[]);
void	calculate_missing_vectors(t_cam *cam);
void	update_cam(t_cam *cam);
void	post_init_cam(t_cam *cam);

void	new_ray(t_cam *cam, t_ray *ray, int x, int y);
void	get_closest_intersection_sp(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_cy(t_data *data, t_ray *ray, t_obj *obj);
void	get_closest_intersection_pl(t_data *data, t_ray *ray, t_obj *obj);
void	exec_launch_rays(t_mlx *mlx, t_data *data, int x, int y);

int		init_data(char *map_path, t_data *data);
void	chang_mesh_size(t_data *data, int keycode);
void	make_rt_file(t_data *data);
void	video_rotate_element(t_sphere *sphere);

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

void	assign_vector(t_matrix_vector *origin_vect, t_matrix_vector *dir_vect,
	t_matrix_vector **new_origin_vect, t_matrix_vector **new_dir_vect)
{
	*new_origin_vect = origin_vect;
	*new_dir_vect = dir_vect;
}

void	limit_to_255(t_color *color);

void	be_highlight(t_color *color)
{
	int	i;

	i = -1;
	while (++i < AXIS)	
		color->rgb[i] += 100;
	limit_to_255(color);	
}

void	actual_mesh_handle(t_data *data, t_obj *mesh,
	t_matrix_vector **origin_vect, t_matrix_vector **dir_vect)
{
	t_color			*color;

	if (mesh)
	{
		if (mesh->type == O_SP)
			color = &((t_sphere *) mesh->ref)->color;
		else if (mesh->type == O_CY)
			color = &((t_cylinder *) mesh->ref)->color;
		else if (mesh->type == O_PL)
			color = &((t_plane *) mesh->ref)->color;
		if (color)
		{
			data->event.color_sav = *color;
			be_highlight(color);		
		}
		data->event.actual_mesh = *mesh;			
	}
	else if (data->event.actual_mesh.ref)
	{			
		if (data->event.actual_mesh.type == O_SP)			
			assign_vector(&((t_sphere *) data->event.actual_mesh.ref)
				->origin_vect, NULL, origin_vect, dir_vect);			
		else if (data->event.actual_mesh.type == O_PL)			
			assign_vector(&((t_plane *) data->event.actual_mesh.ref)
				->origin_vect, &((t_plane *) data->event.actual_mesh.ref)
				->norm_vect, origin_vect, dir_vect);			
		else if (data->event.actual_mesh.type == O_CY)			
			assign_vector(&((t_cylinder *) data->event.actual_mesh.ref)
				->origin_vect, &((t_cylinder *)data->event.actual_mesh.ref)
				->axis_vect, origin_vect, dir_vect);		
	}
}


void	reset(t_data *data)
{
	t_reset_tmps tmps;

	tmps.planes = data->planes;
	tmps.spheres = data->spheres;
	tmps.cylinders = data->cylinders;
	tmps.data_cpy = data->data_cpy;
	tmps.planes_cpy = data->data_cpy->planes;
	tmps.spheres_cpy = data->data_cpy->spheres;
	tmps.cylinders_cpy = data->data_cpy->cylinders;
	*data = *data->data_cpy;
	data->planes = tmps.planes;
	data->spheres = tmps.spheres;
	data->cylinders = tmps.cylinders;
	data->data_cpy = tmps.data_cpy;	
	ft_memcpy(data->planes, tmps.planes_cpy, data->pl_nbr *
		sizeof(t_plane));
	ft_memcpy(data->spheres, tmps.spheres_cpy, data->sp_nbr *
		sizeof(t_sphere));
	ft_memcpy(data->cylinders, tmps.cylinders_cpy, data->cy_nbr *
		sizeof(t_cylinder));
}

void	reset_cam(t_data *data)
{
	data->cam.forward_vect.axis[1] = 0;
	calculate_missing_vectors(&data->cam);
}

void	event_intensity(int keycode, double *intensity)
{
	if (keycode == PLUS && *intensity <= 0.9)
		*intensity += 0.1;
	else if (keycode == MINUS && *intensity >= 0.1)
		*intensity -= 0.1;
}

int	key_event(int keycode, void *param)
{
	t_mlx						*mlx;
	t_data						*data;
	// static t_event_mesh			mesh_enum;
	t_matrix_vector 			*rotate_vect;
	t_matrix_vector 			*transl_vect;

	mlx = (t_mlx *) ((void **) param)[0];
	data = (t_data *) ((void **) param)[1];
	rotate_vect = NULL;
	transl_vect = NULL;
	data->refresh = 1;
	// printf("keycode: %d\n", keycode);
	if (keycode == ESC)
		mlx_loop_end(mlx->connect);
	else if (keycode == RST)	
		reset(data);
	else if (keycode == RST_CM)	
		reset_cam(data);		
	else if (keycode == MESH)	
		data->event.type_mesh = E_MESH;
	else if (keycode == CAM)	
		data->event.type_mesh = E_CAM;
	else if (keycode == LIGHT)	
		data->event.type_mesh = E_SPOTL;
	else if (keycode == AMBL)	
		data->event.type_mesh = E_AMBL;
	else if (data->event.type_mesh == E_CAM)
	{
		event_translate(keycode, trsl_cam, &data->cam, NULL);	
		cam_event_rotate(keycode, &data->cam);
	}
	else if (data->event.type_mesh == E_SPOTL)	
		event_translate(keycode, trsl_about_cam, &data->cam, &data->spotlight.origin_vect);
	else if (data->event.type_mesh == E_MESH)
	{
		actual_mesh_handle(data, NULL, &transl_vect, &rotate_vect);
		if (transl_vect)
			event_translate(keycode, trsl_about_cam, &data->cam, transl_vect);
		if (rotate_vect)
			event_rotate(keycode, rotate_vect);
	}
	if (keycode == MAKE_RT_FILE)
		make_rt_file(data);
	if (keycode == VIDEO_NEXT_FRAME)
	{
		int i = 0;
		while (i < data->sp_nbr)
		{
			video_rotate_element(&data->spheres[i]);
			printf("i: %i\n", i);
			i++;
		}
	}
	if (keycode == CTRL || keycode == CTRL_2)
	{
		data->event.ctrl_ispressed = 1;
	}
	if (data->event.type_mesh == E_MESH && (keycode == PLUS || keycode == MINUS))
		chang_mesh_size(data, keycode);
	if (data->event.type_mesh == E_SPOTL)
	{
		data->spotlight.bulb.origin_vect = data->spotlight.origin_vect;
		event_intensity(keycode, &data->spotlight.intensity);			
	}
	else if (data->event.type_mesh == E_AMBL)
		event_intensity(keycode, &data->ambiant_light.intensity);			
	return (0);
}

void	key_up_event(int keycode, void *param)
{
	t_mlx						*mlx;
	t_data						*data;

	data = (t_data *) ((void **) param)[1];
	if (keycode == CTRL || keycode == CTRL_2)
	{
		data->event.ctrl_ispressed = 0;
	} 
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
	actual_mesh_handle(data, &obj, NULL, NULL);	
}

int	mouse_release(int button, int x, int y, void *param)
{	
	t_data	*data;
	
	data = (t_data *) param;
	if (data->event.actual_mesh.ref)
	{
		data->refresh = 1;
		if (data->event.actual_mesh.type == O_SP)
			((t_sphere *) data->event.actual_mesh.ref)->color
				= data->event.color_sav;
		else if (data->event.actual_mesh.type == O_PL)	
			((t_plane *) data->event.actual_mesh.ref)->color
				= data->event.color_sav;
		else if (data->event.actual_mesh.type == O_CY)			
			((t_cylinder *) data->event.actual_mesh.ref)->color
				= data->event.color_sav;
	}
	return (0);
}

int    mouse_event(int button, int x, int y, void *param)
{
    t_data	*data;

    data = (t_data *) param;
	data->refresh = 1;
	if (button == 1)
	{
		if (x >= 0 && x < 100 && y >= 0 && y < 100)
			return (data->event.legend = (data->event.legend + 1) % 2, 0);
		if (data->event.type_mesh == E_MESH)		
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
