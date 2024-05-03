#include "main.h"

int	init_data(char *map_path, t_data *data);
int	update_cam(t_cam *cam);
int	key_event(int keycode, void *param);
int scroll_event(int button, int x, int y, void *param);
// static void	add_background(int x, int y)
// {
// 	char	*img_data;
// 	int		pxl_pos;
// 	int		bpp;
// 	int		size_line;

// 	img_data_handle(NULL, &img_data, &size_line, &bpp);
// 	while (++x < WIDTH)
// 	{
// 		y = -1;
// 		while (++y < HEIGHT)		
// 			put_pxl(x, y, 0xFFEDCB);		
// 	}
// }

#include <unistd.h>
int	frame(void *param)
{
	t_mlx	*mlx;
	t_data	*data;

	mlx = (t_mlx *) ((void **) param)[0];
	data = (t_data *) ((void **) param)[1];
	usleep(500);
	// static int	refresh;
	//(void) param;
	// refresh = (refresh + 1) % 100;	
	// if (!event->flag && refresh)
	// 	return (0);
	// frame();
	// event->flag = 0;

	mlx->img.img_ptr = mlx_new_image(mlx->connect, WIDTH, HEIGHT);
	mlx->img.img_data = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
		&mlx->img.line_len,	&(int){0});
	launch_rays(mlx, data);
	mlx_put_image_to_window(mlx->connect, mlx->window, mlx->img.img_ptr, 0, 0);
	mlx_destroy_image(mlx->connect, mlx->img.img_ptr);
	return (0);
}

void	launch_mlx_loop(t_mlx *mlx, t_data *data)
{		
	mlx_hook(mlx->window, 17, 0L, mlx_loop_end, mlx->connect);
	mlx_hook(mlx->window, 2, 1L << 0, key_event, (void *[]){mlx, data});
	mlx_mouse_hook(mlx->window, scroll_event, (void *) data);
	mlx_loop_hook(mlx->connect, frame, (void *[]){mlx, data});
	mlx_loop(mlx->connect);
}

int	init_mlx(t_mlx *mlx)
{	
	mlx->connect = mlx_init();
	if (!mlx->connect)
		return (1);
	mlx->window = mlx_new_window(mlx->connect, WIDTH, HEIGHT, "miniRT");
	if (!mlx->window)
		return (mlx_destroy_display(mlx->connect),free(mlx->connect), 1);
	add_exit_struct((void *) mlx, MLX);
	return (0);
}

void	print_cam_content(t_data data)
{	
	printf("data.cam.origin_vect.axis[0]: %f\n",data.cam.origin_vect.axis[0]);
	printf("data.cam.origin_vect.axis[1]: %f\n",data.cam.origin_vect.axis[1]);
	printf("data.cam.origin_vect.axis[2]: %f\n",data.cam.origin_vect.axis[2]);
	printf("data.cam.forward_vect.axis[0]: %f\n",data.cam.forward_vect.axis[0]);
	printf("data.cam.forward_vect.axis[1]: %f\n",data.cam.forward_vect.axis[1]);
	printf("data.cam.forward_vect.axis[2]: %f\n",data.cam.forward_vect.axis[2]);
	printf("data.cam.forward_vect.axis[2]: %f\n",data.cam.forward_vect.axis[2]);	
	printf("data.cam.up_vect.axis[0]: %f\n",data.cam.up_vect.axis[0]);
	printf("data.cam.up_vect.axis[1]: %f\n",data.cam.up_vect.axis[1]);
	printf("data.cam.up_vect.axis[2]: %f\n",data.cam.up_vect.axis[2]);
	printf("data.cam.right_vect.axis[0]: %f\n",data.cam.right_vect.axis[0]);
	printf("data.cam.right_vect.axis[1]: %f\n",data.cam.right_vect.axis[1]);
	printf("data.cam.right_vect.axis[2]: %f\n",data.cam.right_vect.axis[2]);
	printf("resol0: %f\n",data.cam.resol[0]);
	printf("resol1: %f\n",data.cam.resol[1]);
	printf("fov: %f\n",data.cam.fov_deg);
	printf("fov: %f\n",data.cam.fov_rad);
	printf("scale: %f\n",data.cam.scale);
	printf("aspect: %f\n",data.cam.aspect);
	printf("focal_len: %f\n",data.cam.focal_len);
}

void	print_sphere(t_sphere sphere)
{
	printf("sphere.origin_vect.axis[0]: %f\n", sphere.origin_vect.axis[0]);
	printf("sphere.origin_vect.axis[1]: %f\n", sphere.origin_vect.axis[1]);
	printf("sphere.origin_vect.axis[2]: %f\n", sphere.origin_vect.axis[2]);
	printf("sphere.diameter: %f\n", sphere.diameter);
	printf("spheres.square_radius: %f\n", sphere.square_radius);
	printf("spheres.color.rgb[0]: %i\n", sphere.color.rgb[0]);
	printf("spheres.color.rgb[1]: %i\n", sphere.color.rgb[1]);
	printf("spheres.color.rgb[2]: %i\n", sphere.color.rgb[2]);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_data 	data;

	if (argc != 2)
		return (display_error("arg number not valid\n"), 1);
	if (parse(&data, argv[1]) == 0)
		return (display_error(".rt file not valid\n"), 2);
	if (init_data(argv[1], &data) == 0)
		return (display_error("data init. error\n"), 3);
	post_init_cam(&data.cam);
	update_cam(&data.cam);
	if (init_mlx(&mlx))
		return (4);
	launch_mlx_loop(&mlx, &data);
	flush_exit_struct();
	return (0);
}
