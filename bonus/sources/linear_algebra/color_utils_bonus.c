#include "color_utils_bonus.h"

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

/**========================================================================
 *                           GET_AVERAGE_COLOR
 *========================================================================**/
void	get_average_color(t_color *a, t_color *b, t_color *average)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		average->rgb[i] = (a->rgb[i] + b->rgb[i]) * 0.5;
}

/**========================================================================
 *                           GET_AVERAGE_COLORS
 *========================================================================**/
void	get_average_colors(t_color colors[], int n_colors, t_color *average)
{
	int	i;
	int	j;
	double	inv_n_colors;

	average->rgb[0] = 0;
	average->rgb[1] = 0;
	average->rgb[2] = 0;
	i = -1;
	while (++i < n_colors)
	{
		j = -1;
		while (++j < AXIS)
			average->rgb[j] += colors[i].rgb[j];		
	}
	inv_n_colors = 1.0f / n_colors;
	j = -1;
	while (++j < AXIS)
		average->rgb[j] *= inv_n_colors;
}
