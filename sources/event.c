# include "x_mini_struct.h"
# include "mlx.h"
void	trsl_cam(t_cam *cam, double values[]);
void	rotate_cam(t_cam *cam, double angle, int axe[]);

static void	cam_event(int keycode, t_cam *cam)
{
	if (keycode == UP)
		trsl_cam(cam, (double []){0, -1, 0});		
	if (keycode == DWN)	
		trsl_cam(cam, (double []){0, 1, 0});	
	if (keycode == LFT)	
		trsl_cam(cam, (double []){1, 0, 0});	
	if (keycode == RGHT)	
		trsl_cam(cam, (double []){-1, 0, 0});
	if (keycode == FWRD)	
		trsl_cam(cam, (double []){0, 0, 1});
	if (keycode == BACK)	
		trsl_cam(cam, (double []){0, 0, -1});

    if (keycode == R_LFT)	
		rotate_cam(cam, 0.1, (int []){1, 0, 0});
    if (keycode == R_RGHT)	
		rotate_cam(cam, -0.1, (int []){1, 0, 0});
    if (keycode == R_UP)	
		rotate_cam(cam, 0.1, (int []){0, 1, 0});
    if (keycode == R_DWN)	
		rotate_cam(cam, -0.1, (int []){0, 1, 0});
     if (keycode == S_LFT)	
		rotate_cam(cam, 0.1, (int []){0, 0, 1});
    if (keycode == S_RGHT)	
		rotate_cam(cam, -0.1, (int []){0, 0, 1});
} 	

int	key_event(int keycode, void *param)
{
	t_mlx	*mlx;
	t_data	*data;

	mlx = (t_mlx *) ((void **) param)[0];
	data = (t_data *) ((void **) param)[1];
	printf("keycode: %d\n", keycode);
	cam_event(keycode, &data->cam);
	if (keycode == ESC)
		mlx_loop_end(mlx->connect);
	return (0);
}
