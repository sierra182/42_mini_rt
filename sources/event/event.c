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

void	limit_to_255(t_color *color);

/**========================================================================
 *                           ASSIGN_VECTOR
 *========================================================================**/
void	assign_vector(t_matrix_vector *origin_vect, t_matrix_vector *dir_vect,
	t_matrix_vector **new_origin_vect, t_matrix_vector **new_dir_vect)
{
	*new_origin_vect = origin_vect;
	*new_dir_vect = dir_vect;
}

/**========================================================================
 *                           BE_HIGHLIGHT
 *========================================================================**/
void	be_highlight(t_color *color)
{
	int	i;

	i = -1;
	while (++i < AXIS)	
		color->rgb[i] += 100;
	limit_to_255(color);	
}

/**========================================================================
 *                           ACTUAL_MESH_HANDLE
 *========================================================================**/
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

/**========================================================================
 *                           RESET
 *========================================================================**/
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

/**========================================================================
 *                           RESET_CAM
 *========================================================================**/
void	reset_cam(t_data *data)
{
	data->cam.forward_vect.axis[1] = 0;
	calculate_missing_vectors(&data->cam);
}

/**========================================================================
 *                           EVENT_INTENSITY
 *========================================================================**/
void	event_intensity(int keycode, double *intensity)
{
	if (keycode == PLUS && *intensity <= 0.9)
		*intensity += 0.1;
	else if (keycode == MINUS && *intensity >= 0.1)
		*intensity -= 0.1;
}

/**========================================================================
 *                           KEY_UP_EVENT
 *========================================================================**/
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

/**========================================================================
 *                           EVENT_LAUNCH_RAYS
 *========================================================================**/
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

