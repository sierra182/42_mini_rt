/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_trsf_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:42:04 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 15:42:05 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_trsf_bonus.h"

/**========================================================================
 *                           SET_MATRIX_ROTATION
 *========================================================================**/
void	set_matrix_rotation(t_matrix_vector matrix[], double angle, int axe[])
{
	angle *= M_PI / 180.0;
	if (axe[0])
	{
		matrix[1].axis[1] = cos(angle);
		matrix[1].axis[2] = -sin(angle);
		matrix[2].axis[1] = sin(angle);
		matrix[2].axis[2] = cos(angle);
	}
	else if (axe[1])
	{
		matrix[0].axis[0] = cos(angle);
		matrix[0].axis[2] = sin(angle);
		matrix[2].axis[0] = -sin(angle);
		matrix[2].axis[2] = cos(angle);
	}
	else if (axe[2])
	{
		matrix[0].axis[0] = cos(angle);
		matrix[0].axis[1] = -sin(angle);
		matrix[1].axis[0] = sin(angle);
		matrix[1].axis[1] = cos(angle);
	}
}

/**========================================================================
 *                           SET_MATRIX_SCALE
 *========================================================================**/
void	set_matrix_scale(double matrix[][AXIS], double scale[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		matrix[i][i] = scale[i];
}

/**========================================================================
 *                           SET_MATRIX_TRANSLATE
 *========================================================================**/
void	set_matrix_translate(t_matrix_vector matrix[], double trans[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		matrix[i].axis[AXIS] = trans[i];
}
