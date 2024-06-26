/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamping_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:38:28 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 15:38:29 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clamping_bonus.h"

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
 *                           CLAMP_0
 *========================================================================**/
double	clamp_0(double num)
{
	if (num < 0)
		return (0.0);
	return (num);
}

/**========================================================================
 *                           CLAMP_rgb_0
 *========================================================================**/
void	clamp_rgb_0(t_color *color)
{
	int	i;

	i = -1;
	while (++i < AXIS)
		if (color->rgb[i] < 0)
			color->rgb[i] = 0;
}

/**========================================================================
 *                           CLAMP_1
 *========================================================================**/
double	clamp_1(double num)
{
	if (num > 1)
		return (1.0);
	return (num);
}
