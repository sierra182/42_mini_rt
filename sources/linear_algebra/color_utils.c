#include "color_utils.h"

void	clamp_255(t_color *color)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		if (color->rgb[i] > 255)
			color->rgb[i] = 255;
}

int	get_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char []){b, g, r, 0});
}

// void clamp_color(t_color *color, int min, int max) {
//     int i;
//     for (i = 0; i < AXIS; ++i) {
//         if (color->rgb[i] < min) color->rgb[i] = min;
//         if (color->rgb[i] > max) color->rgb[i] = max;
//     }
// }