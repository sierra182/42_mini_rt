/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:08:30 by seblin            #+#    #+#             */
/*   Updated: 2024/01/23 13:24:26 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "setup.h"

void	set_matrix_persp(double matrix[][MTX], double fov, double aspect)
{
	double	f;

	f = 1;
	if (tan(fov * M_PI / 360.0))
		f = 1.0 / tan(fov * M_PI / 360.0);
	matrix[0][0] = aspect * f;
	matrix[1][1] = f;
	matrix[2][2] = 1;
	matrix[2][3] = 0;
	matrix[3][2] = -1.0;
	matrix[MTX - 1][MTX - 1] = 0;
}

void	set_matrix_rotation(double matrix[][MTX], double angle, int *axe)
{
	angle *= M_PI / 180.0;
	if (axe[0])
	{
		matrix[1][1] = cos(angle);
		matrix[1][2] = -sin(angle);
		matrix[2][1] = sin(angle);
		matrix[2][2] = cos(angle);
	}
	else if (axe[1])
	{
		matrix[0][0] = cos(angle);
		matrix[0][2] = sin(angle);
		matrix[2][0] = -sin(angle);
		matrix[2][2] = cos(angle);
	}
	else if (axe[2])
	{
		matrix[0][0] = cos(angle);
		matrix[0][1] = -sin(angle);
		matrix[1][0] = sin(angle);
		matrix[1][1] = cos(angle);
	}
}

void	set_matrix_translate(double matrix[][MTX], double trans[])
{
	int	i;

	i = -1;
	while (++i < MTX - 1)
		matrix[i][MTX - 1] = trans[i];
}

void	set_matrix_scale(double matrix[][MTX], double scale[])
{
	int	i;

	i = -1;
	while (++i < MTX - 1)
		matrix[i][i] = scale[i];
}
