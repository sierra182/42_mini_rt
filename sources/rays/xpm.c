#include "se_mini_struct.h"

static void	add_xpm_item(t_mlx *mlx, int pixels[], t_img *img, int offsets[])
{
	const double	inverse_eight = 0.125;
	int				pxl_pos_item;
	int				pxl_pos;

	if (pixels[0] >= 0 && pixels[0] < WIDTH
		&& pixels[1] >= 0 && pixels[1] < HEIGHT)
	{
		pxl_pos = pixels[0] * mlx->img.bpp * inverse_eight
			+ pixels[1] * mlx->img.line_len;
		pxl_pos_item = (pixels[0] - offsets[0]) * img->bpp * inverse_eight
			+ (pixels[1] - offsets[1]) * img->line_len;
		if (*(unsigned int *)(img->img_data + pxl_pos_item)
			!= img->alpha_color)
			*(unsigned int *)(mlx->img.img_data + pxl_pos)
				= *(unsigned int *)(img->img_data + pxl_pos_item);
	}
}

void	add_xpm_items(t_mlx *mlx, t_data *data, int x, int y)
{
	if (x >= 0 && x <= 100 && y >= 0 && y < 100)
		add_xpm_item(mlx, (int []){x, y}, &mlx->img_items.logo,
			(int []){0, 0});
	if (x >= WIDTH - 100 && y >= 0 && y < 100)
	{
		if (data->event.actual_mode == E_CAM)
			add_xpm_item(mlx, (int []){x, y}, &mlx->img_items.cam,
				(int []){WIDTH - 100, 0});
		else if (data->event.actual_mode == E_SPOTL)
			add_xpm_item(mlx, (int []){x, y}, &mlx->img_items.bulb,
				(int []){WIDTH - 100, 0});
		else if (data->event.actual_mode == E_AMBL)
			add_xpm_item(mlx, (int []){x, y}, &mlx->img_items.amb,
				(int []){WIDTH - 100, 0});
		else if (data->event.actual_mode == E_MESH)
			add_xpm_item(mlx, (int []){x, y}, &mlx->img_items.sph,
				(int []){WIDTH - 100, 0});
	}
	if (data->event.legend && x >= WIDTH - 792 && y >= HEIGHT - 200)
		add_xpm_item(mlx, (int []){x, y}, &mlx->img_items.legend,
			(int []){WIDTH - 792, HEIGHT - 200});
}
