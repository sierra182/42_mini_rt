# include "se_mini_struct.h"
# include "x_matrix.h"
#include "libft.h"
void	video_rotate_cogs(t_cylinder *cyl, int	i, int cyl_nbr);
void	rotate_pendulum(t_sphere *sphere, int i);
void	video_move_cam(t_cam *cam);
void	video_move_light(t_spotlight *light);
void	make_rt_file(t_data *data);

int	generate_video_frames(t_data *data, char **envp)
{
	int	i;
	static int	j = 0;

	data->is_gen_vid = 0;
	i = 0;
	while (envp[i])
	{
		// printf("envp[%i] = %s\n", i, envp[i]);
		if (ft_strncmp(envp[i], "VIDEO_GEN=true", 20) == 0)
		{
			data->is_gen_vid = 1;
			break ;
		}
		i++;
	}
	if (data->is_gen_vid == 0)
		return (1);
	i = 0;
	while(i < 32)
	{
		// printf("i = %d\n", i);
		// i = 0;
		// while (i < data->cy_nbr)
		// {
		// 	video_rotate_cogs(&data->cylinders[i], i, data->cy_nbr);
		// 	i++;
		// }
		// rotate_pendulum(&data->spheres[0] , j);
		// video_move_cam(&data->cam);
		// video_move_light(&data->spotlight);
		// make_rt_file(data);
		// j++;
		i++;
	}
	return (1);
}

