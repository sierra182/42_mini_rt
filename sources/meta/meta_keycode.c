#include "x_mini_struct.h"

void	make_rt_file(t_data *data);
void	video_rotate_element(t_sphere *sphere);

/**========================================================================
 *                           META_KEYCODE
 *========================================================================**/
void	meta_keycode(int keycode, t_data *data)
{
	int	i;

	if (keycode == MAKE_RT_FILE)
		make_rt_file(data);
	if (keycode == VIDEO_NEXT_FRAME)
	{
		i = 0;
		while (i < data->sp_nbr)
			video_rotate_element(&data->spheres[i++]);
	}
}