# include "x_mini_struct.h"
# include "mlx.h"
void	trsl_mesh(t_cam *cam, double values[], t_enum_event_mesh type);
void	rotate_cam(t_cam *cam, double angle, int axe[]);
void	update_cam(t_cam *cam);

static void event_rotate(int keycode, void *mesh, t_enum_event_mesh type)
{
    double  r;
	
    r = .05;
    if (keycode == R_LFT)	
		rotate_mesh(mesh, type, r, (int []){1, 0, 0});
    else if (keycode == R_RGHT)	
		rotate_mesh(mesh, type,  -r, (int []){1, 0, 0});
    else if (keycode == R_UP)	
		rotate_mesh(mesh, type, r, (int []){0, 1, 0});
    else if (keycode == R_DWN)	
		rotate_mesh(mesh, type, -r, (int []){0, 1, 0});
    else if (keycode == S_LFT)	
		rotate_mesh(mesh, type, 50 * r, (int []){0, 0, 1});
    else if (keycode == S_RGHT)	
		rotate_mesh(mesh, type, -50 * r, (int []){0, 0, 1});
}

static void	event_translate(int keycode, void *mesh, t_enum_event_mesh type)
{
    double t;

    t = 0.05;
	if (keycode == UP)
		trsl_mesh(mesh, type, (double []){0.0, -t, 0.0});		
	else if (keycode == DWN)	
		trsl_mesh(mesh, type, (double []){0.0, t, 0.0});	
	else if (keycode == LFT)	
		trsl_mesh(mesh, type, (double []){t, 0.0, 0.0});	
	else if (keycode == RGHT)	
		trsl_mesh(mesh, type, (double []){-t, 0.0, 0.0});
	else if (keycode == FWRD)	
		trsl_mesh(mesh, type, (double []){0.0, 0.0, 20 * t});
	else if (keycode == BACK)	
		trsl_mesh(mesh, type, (double []){0.0, 0.0, -20 * t});
} 	

int	key_event(int keycode, void *param)
{
	t_mlx						*mlx;
	t_data						*data;
	static t_enum_event_mesh	mesh = CAM;

	mlx = (t_mlx *) ((void **) param)[0];
	data = (t_data *) ((void **) param)[1];
	printf("keycode: %d\n", keycode);
	if (keycode == MESH)	
		mesh = (mesh + 1) % MESH_END;	
	event_translate(keycode, &data->cam, mesh);
	if (mesh == CAM)
    	event_rotate(keycode, &data->cam);	
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