# include "x_mini_struct.h"
# include "mlx.h"
void	trsl_cam(t_cam *cam, double values[]);
void	rotate_cam(t_cam *cam, double angle, int axe[]);
void	update_cam(t_cam *cam);

static void cam_event_rotate(int keycode, t_cam *cam)
{
    double  r;

    r = 1;
    if (keycode == R_LFT)	
		rotate_cam(cam, r, (int []){1, 0, 0});
    else if (keycode == R_RGHT)	
		rotate_cam(cam, -r, (int []){1, 0, 0});
    else if (keycode == R_UP)	
		rotate_cam(cam, r, (int []){0, 1, 0});
    else if (keycode == R_DWN)	
		rotate_cam(cam, -r, (int []){0, 1, 0});
    else if (keycode == S_LFT)	
		rotate_cam(cam, 50 * r, (int []){0, 0, 1});
    else if (keycode == S_RGHT)	
		rotate_cam(cam, -50 * r, (int []){0, 0, 1});
}

static void	cam_event_translate(int keycode, t_cam *cam)
{
    double t;

    t = 0.1;
	if (keycode == UP)
		trsl_cam(cam, (double []){0.0, -t, 0.0});		
	else if (keycode == DWN)	
		trsl_cam(cam, (double []){0.0, t, 0.0});	
	else if (keycode == LFT)	
		trsl_cam(cam, (double []){t, 0.0, 0.0});	
	else if (keycode == RGHT)	
		trsl_cam(cam, (double []){-t, 0.0, 0.0});
	else if (keycode == FWRD)	
		trsl_cam(cam, (double []){0.0, 0.0, t});
	else if (keycode == BACK)	
		trsl_cam(cam, (double []){0.0, 0.0, -t});
} 	

int	key_event(int keycode, void *param)
{
	t_mlx	*mlx;
	t_data	*data;

	mlx = (t_mlx *) ((void **) param)[0];
	data = (t_data *) ((void **) param)[1];
	printf("keycode: %d\n", keycode);
	cam_event_translate(keycode, &data->cam);
    cam_event_rotate(keycode, &data->cam);
	if (keycode == ESC)
		mlx_loop_end(mlx->connect);
	return (0);
}
int    scroll_event(int button, int x, int y, void *param)
{
    t_data	*data;

    data = (t_data *) param;
    if (button == 5)
        data->cam.fov_deg++;
    else if (button == 4)
        data->cam.fov_deg--;
    update_cam(&data->cam);
	return (0);
}