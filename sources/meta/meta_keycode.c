#include "se_mini_struct.h"

void	make_rt_file(t_data *data);
void	video_rotate_element(t_sphere *sphere, int obj_nbr);
void	make_bin_file(t_data *data, t_mlx *mlx);

/**========================================================================
 *                           META_KEYCODE
 *========================================================================**/
void	meta_keycode(int keycode, t_data *data, t_mlx *mlx)
{
	int	i;

	if (keycode == MAKE_RT_FILE)
		make_rt_file(data);
	// if (keycode == MAKE_BIN_FILE)
	// 	make_bin_file(data, mlx);
	if (keycode == VIDEO_NEXT_FRAME)
	{
		i = 0;
		while (i < data->sp_nbr)
		{
			video_rotate_element(&data->spheres[i], i);
			i++;
		}
	}
}