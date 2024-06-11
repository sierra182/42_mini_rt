#include "color_utils_bonus.h"

/**========================================================================
 *                           CLAMP_255
 *========================================================================**/
void	clamp_255(t_color *color)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		if (color->rgb[i] > 255)
			color->rgb[i] = 255;
}

/**========================================================================
 *                           GET_COLOR
 *========================================================================**/
int	get_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char []){b, g, r, 0});
}

/**========================================================================
 *                           NORMALIZE_ZERO_ONE
 *========================================================================**/
void	normalize_zero_one(double *scalar_product, int clamp_flag)
{
	if (!clamp_flag)
		*scalar_product = (*scalar_product + 1) * 0.5;
	else if (*scalar_product >= -1 && *scalar_product < 0)
		*scalar_product = 0;
}
