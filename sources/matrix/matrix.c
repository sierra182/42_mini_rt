/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:58:38 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:58:39 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

/**========================================================================
 *                           APPLY_MATRIX
 *========================================================================**/
void	apply_matrix(t_matrix_vector matrix[], t_matrix_vector *vector,
	t_matrix_vector *applied_vect)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MTX)
	{
		applied_vect->axis[i] = 0.0;
		j = -1;
		while (++j < MTX)
			applied_vect->axis[i] += (matrix[i].axis[j]
					* vector->axis[j]);
	}
}

/**========================================================================
 *                           MULTIPLY_ROWBYCOL
 *========================================================================**/
static double	multiply_rowbycol(t_matrix_vector *a_row, t_matrix_vector b[],
	int col)
{
	double	rslt;
	int		i;

	rslt = 0;
	i = -1;
	while (++i < MTX)
		rslt += a_row->axis[i] * b[i].axis[col];
	return (rslt);
}

/**========================================================================
 *                           MULTIPLY_MATRIX
 *========================================================================**/
void	multiply_matrix(t_matrix_vector a[], t_matrix_vector b[],
	t_matrix_vector mult_matrix[])
{
	int	i;
	int	j;

	i = -1;
	while (++i < MTX)
	{
		j = -1;
		while (++j < MTX)
			mult_matrix[i].axis[j] = multiply_rowbycol(&a[i], b, j);
	}
}

/**========================================================================
 *                           INIT_MATRIX
 *========================================================================**/
void	init_matrix(t_matrix_vector matrix[])
{
	int	i;
	int	j;

	i = -1;
	while (++i < MTX)
	{
		matrix[i].axis[i] = 1.0;
		j = -1;
		while (++j < MTX)
			if (i != j)
				matrix[i].axis[j] = 0.0;
	}
}
