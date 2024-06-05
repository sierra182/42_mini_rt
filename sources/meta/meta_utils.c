# include "se_mini_struct.h"
# include "x_matrix.h"

void	generate_video_frames(t_data *data)
{
	static int	j = 0;
	int	i;

	while(i < 32)
	{
		i = 0;
		while (i < data->cy_nbr)
		{
			video_rotate_cogs(&data->cylinders[i], i, data->cy_nbr);
			i++;
		}
		rotate_pendulum(&data->spheres[0] , j);
		video_move_cam(&data->cam);
		video_move_light(&data->spotlight);
		j++;
	}
}