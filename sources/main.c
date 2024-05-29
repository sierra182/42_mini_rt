#include "main.h"

# include <stdlib.h>
# include "ft_printf.h"
# include "x_exit.h"
# include "libft.h"
# include "mlx.h"

int		init_data(char *map_path, t_data *data);
int		key_event(int keycode, void *param);
int		mouse_event(int button, int x, int y, void *param);
void	display_error(char *error);
int		parse(t_data *data, char *map_path);
void	launch_rays(t_mlx *mlx, t_data *data);
int	key_up_event(int keycode, void *param);

/**========================================================================
 *                             COMMENTS
 *! taille maximal input file = 1024 chars. peut etre modifie...
 *! element count commented out (see parsing)
 *! parsing error : element not taken into account when line starts with ' '  
 *! 2 lines commented in parsing to be taken out!  
 *========================================================================**/

int	get_color(unsigned char r, unsigned char g, unsigned char b);

int	frame(void *param)
{
	t_mlx	*mlx;
	t_data	*data;
			
	mlx = (t_mlx *) ((void **) param)[0];
	data = (t_data *) ((void **) param)[1];
	if (!data->refresh)
		return (0);	
	data->refresh = 0;
	launch_rays(mlx, data);
	mlx_put_image_to_window(mlx->connect, mlx->window, mlx->img.img_ptr, 0, 0);	
	return (0);
}

int	mouse_release(int button, int x, int y, void *param)
{	
	t_data	*data;
	
	data = (t_data *) param;
	if (data->event.actual_mesh.ref)
	{
		data->refresh = 1;
		if (data->event.actual_mesh.type == O_SP)
			((t_sphere *) data->event.actual_mesh.ref)->color
				= data->event.color_sav;
		else if (data->event.actual_mesh.type == O_PL)	
			((t_plane *) data->event.actual_mesh.ref)->color
				= data->event.color_sav;
		else if (data->event.actual_mesh.type == O_CY)			
			((t_cylinder *) data->event.actual_mesh.ref)->color
				= data->event.color_sav;
	}
	return (0);
}
void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);
void	pre_transform(t_data *data)
{
	int	i;
	double offset;
	double n_offset;
	double space;

	space = 15;
	i = -1;
	offset = 0;
	while (++i < data->cy_nbr *.25)
	{
		trsl_mesh(NULL, &data->cylinders[i].origin_vect, (double []){0, 0, offset});
		offset += space;
	}
	offset = 0;
	while (i < data->cy_nbr * 0.50)
	{
		offset += space;
		trsl_mesh(NULL, &data->cylinders[i].origin_vect, (double []){offset, 0, 0});
		i++;
	}
	n_offset = 0;
	while (i < data->cy_nbr * 0.75)
	{
		n_offset += space;
		trsl_mesh(NULL, &data->cylinders[i].origin_vect, (double []){offset, 0, n_offset});
		i++;
	}
	// offset = n_offset;
	while (i < data->cy_nbr * 1)
	{
		offset -= space;
		trsl_mesh(NULL, &data->cylinders[i].origin_vect, (double []){offset,  0, n_offset});
		i++;
	}
}
// void pre_transform(t_data *data)
// {
//     int i;
//     int x_offset, y_offset, z_offset;
//     int grid_size;
//     int side_length;

//     // Définir la taille de la grille (nombre de cylindres par côté)
//     side_length = ceil(cbrt(data->cy_nbr)); // racine cubique arrondie au supérieur pour avoir une grille suffisamment grande

//     i = 0;
//     for (z_offset = 0; z_offset < side_length && i < data->cy_nbr; z_offset++)
//     {
//         for (y_offset = 0; y_offset < side_length && i < data->cy_nbr; y_offset++)
//         {
//             for (x_offset = 0; x_offset < side_length && i < data->cy_nbr; x_offset++)
//             {
//                 trsl_mesh(NULL, &data->cylinders[i].origin_vect, (double []){x_offset * 30, y_offset * 30, z_offset * 30});
//                 i++;
//             }
//         }
//     }
// }

void	launch_mlx_loop(t_mlx *mlx, t_data *data)
{		
	// pre_transform(data);
	mlx_hook(mlx->window, 17, 0L, mlx_loop_end, mlx->connect);
	mlx_hook(mlx->window, 2, 1L << 0, key_event, (void *[]){mlx, data});
	mlx_hook(mlx->window, 3, 1L << 1, key_up_event, (void *[]){mlx, data});
	mlx_mouse_hook(mlx->window, mouse_event, (void *) data);
	mlx_hook(mlx->window, 5, 1L << 3, mouse_release, (void *) data);
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
	mlx->img.img_ptr = mlx_new_image(mlx->connect, WIDTH, HEIGHT);
	mlx->img.img_data = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
	&mlx->img.line_len,	&(int){0});
	add_exit_struct((void *) mlx, MLX);
	return (0);
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
	if (init_mlx(&mlx))
		return (4);	
	launch_mlx_loop(&mlx, &data);		
	flush_exit_struct();
	return (0);
}
