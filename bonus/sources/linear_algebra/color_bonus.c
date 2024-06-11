#include "color_bonus.h"

/**========================================================================
 *                           ADD_COLOR
 *========================================================================**/
void	add_color(t_color *a, t_color *b, t_color *sum_color)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		sum_color->rgb[i] = a->rgb[i] + b->rgb[i];
}

/**========================================================================
 *                           SUBTRACT_COLOR
 *========================================================================**/
void	subtract_color(t_color *a, t_color *b, t_color *subt_color)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		subt_color->rgb[i] = a->rgb[i] - b->rgb[i];
}

/**========================================================================
 *                           SCALE_COLOR
 *========================================================================**/
void	scale_color(t_color *color, double scaler, t_color *scaled_color)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		scaled_color->rgb[i] = color->rgb[i] * scaler;
}

/**========================================================================
 *                           MULTIPLY_COLOR
 *========================================================================**/
void	multiply_color(t_color *a, t_color *b, t_color *mult_color)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		mult_color->rgb[i] = a->rgb[i] * b->rgb[i];
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
