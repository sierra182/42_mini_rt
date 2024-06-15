#include "event_bonus.h"

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
 *                           HANDLE_MESH_COLOR_UPDATE
 *========================================================================**/
void	handle_mesh_color_update(t_data *data, t_obj *mesh)
{
	int		i;
	t_color	*color;

	color = NULL;
	if (mesh->type == O_SP)
		color = &((t_sphere *) mesh->ref)->color;
	else if (mesh->type == O_CY)
		color = &((t_cylinder *) mesh->ref)->color;
	else if (mesh->type == O_PL)
		color = &((t_plane *) mesh->ref)->color;
	if (color)
	{
		data->event.color_sav = *color;
		i = -1;
		while (++i < AXIS)
			color->rgb[i] += 255 - color->rgb[i];
	}
	data->event.actual_mesh = *mesh;
}

/**========================================================================
 *                           ACTUAL_MESH_HANDLE
 *========================================================================**/
void	actual_mesh_handle(t_data *data, t_obj *mesh,
	t_matrix_vector **origin_vect, t_matrix_vector **dir_vect)
{
	if (mesh)
		handle_mesh_color_update(data, mesh);
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
	if (obj.ref && !is_behind_cam(obj.t)) //!modif mandat
		actual_mesh_handle(data, &obj, NULL, NULL);
}
