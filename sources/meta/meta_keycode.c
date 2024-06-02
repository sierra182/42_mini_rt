#include "se_mini_struct.h"
#include <unistd.h>
void	make_rt_file(t_data *data);
void	video_rotate_spheres(t_sphere *sphere, int obj_nbr, int sp_nbr);
void	make_bin_file(t_data *data, t_mlx *mlx);
void	video_rotate_cylinders(t_cylinder *cyl, int obj_num, int cyl_nbr);
void	video_rotate_cam(t_cam *cam);
void	video_rotate_light(t_spotlight *light);

/**========================================================================
 *                           META_KEYCODE
 *========================================================================**/
void	meta_keycode(int keycode, t_data *data, t_mlx *mlx)
{
	int	i;

	if (keycode == MAKE_RT_FILE)
		make_rt_file(data);
	if (keycode == MAKE_BIN_FILE)
		make_bin_file(data, mlx);
	if (keycode == VIDEO_NEXT_FRAME)
	{
		i = 0;
		while (i < data->sp_nbr)
		{
			video_rotate_spheres(&data->spheres[i], i, data->sp_nbr);
			i++;
		}
		i = 0;
		while (i < data->cy_nbr)
		{
			video_rotate_cylinders(&data->cylinders[i], i, data->cy_nbr);
			i++;
		}
		video_rotate_cam(&data->cam);
		video_rotate_light(&data->spotlight);
	}
}