#include "se_mini_struct.h"
#include "mlx.h"
#include "libft.h"

void	save_image_reference(t_data *data, t_mlx *mlx)
{
	int bits_per_pixel;
	int size_line;
	int endian;
	char *data_addr;

	ft_bzero(data->img_ref, 20);
	data_addr = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.line_len, &(int){0});
	ft_strlcpy(data->img_ref, data_addr, ft_strlen(data_addr) + 1);
	printf("data_addr,     %s\n", data_addr);
	printf("data->img_ref: %s\n", data->img_ref);
}

void save_image_data_to_bin(char *filename, char *data_addr, int width, int height, int size_line)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    for (int y = 0; y < height; y++)
    {
        fwrite(data_addr + y * size_line, 1, size_line, file);
    }

    fclose(file);
}


// save_image_data_to_bin(char *filename, char *data_addr, int width, int height, int size_line)