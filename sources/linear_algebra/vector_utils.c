/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:58:08 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:58:09 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_utils.h"

/**========================================================================
 *                           INVERT_VECTOR
 *========================================================================**/
void	invert_vector(double ori[], double dir[],
	double inv_ori[], double inv_dir[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
	{
		inv_ori[i] = ori[i] + dir[i];
		inv_dir[i] = -dir[i];
	}
}

/**========================================================================
 *                           SYMMETRIZE_VECTOR
 *========================================================================**/
double	*symmetrize_vector(double vect[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		vect[i] = -vect[i];
	return (vect);
}

/**========================================================================
 *                           GET_VECTOR_MAGNITUDE
 *========================================================================**/
double	get_vector_magnitude(double vector[])
{
	return (sqrt(pow(vector[0], 2) + pow(vector[1], 2)
			+ pow(vector[2], 2)));
}

/**========================================================================
 *                           SELF_NORMALIZE_VECTOR
 *========================================================================**/
void	self_normalize_vector(double vector[])
{
	int		i;
	double	magnitude;
	double	inverse_mag;

	magnitude = get_vector_magnitude(vector);
	if (!magnitude)
		return ;
	inverse_mag = 1 / magnitude;
	i = -1;
	while (++i < AXIS)
		vector[i] *= inverse_mag;
}

/**========================================================================
 *                           NORMALIZE_VECTOR
 *========================================================================**/
void	normalize_vector(double vector[], double magnitude, double norm_vect[])
{
	int		i;
	double	inverse_mag;

	if (!magnitude)
		return ;
	inverse_mag = 1 / magnitude;
	i = -1;
	while (++i < AXIS)
		norm_vect[i] = vector[i] * inverse_mag;
}
