#include "se_mini_struct_bonus.h"
#include <unistd.h>
void	make_rt_file(t_data *data);
void	video_rotate_spheres(t_sphere *sphere, int obj_nbr, int sp_nbr);
void	make_bin_file(t_data *data, t_mlx *mlx);
void	video_rotate_cylinders(t_cylinder *cyl, int obj_num, int cyl_nbr);
void	video_rotate_cam(t_cam *cam);
void	video_rotate_light(t_spotlight *light);
void	video_trans_mesh(void *mesh, int mesh_num, int mesh_nbr);
void	video_rotate_cogs(t_cylinder *cyl, int	i, int cyl_nbr);
void	rotate_pendulum(t_sphere *sphere, int i);
void	video_move_cam(t_cam *cam);
void	video_move_light(t_spotlight *light);


/**========================================================================
 *                           META_KEYCODE
 *========================================================================**/
void	meta_keycode(int keycode, t_data *data, t_mlx *mlx)
{
	int	i;
	static int	j = 0;

	if (keycode == MAKE_RT_FILE)
		make_rt_file(data);
	if (keycode == MAKE_BIN_FILE)
	{
		// data->event.antia = 2;
		make_bin_file(data, mlx);
	}
	// if (keycode == VIDEO_NEXT_FRAME)
	// {
	// 	i = 0;
	// 	while (i < data->cy_nbr)
	// 	{
	// 		video_rotate_cogs(&data->cylinders[i], i, data->cy_nbr);
	// 		i++;
	// 	}
	// 	rotate_pendulum(&data->spheres[0] , j);
	// 	video_move_cam(&data->cam);
	// 	video_move_light(&data->spotlight);
	// 	j++;
	// }

	
	// *** VIDEO ALL_SHAPES ***
	// if (keycode == VIDEO_NEXT_FRAME)
	// {
	// 	i = 0;
	// 	while (i < data->sp_nbr)
	// 	{
	// 		video_rotate_spheres(&data->spheres[i], i, data->sp_nbr);
	// 		i++;
	// 	}
	// 	i = 0;
	// 	while (i < data->cy_nbr)
	// 	{
	// 		video_rotate_cylinders(&data->cylinders[i], i, data->cy_nbr);
	// 		i++;
	// 	}
	// 	video_rotate_cam(&data->cam);
	// 	video_rotate_light(&data->spotlight);
	// }
	// if (keycode == TRANSFORM_MESH)
	// {
	// 	i = 0;
	// 	while (i < data->cy_nbr + data->sp_nbr)
	// 	{
	// 		video_trans_mesh(&data->cylinders[i], i, data->cy_nbr);
	// 		i++;
	// 	}
	// }
}