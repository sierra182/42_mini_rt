/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:39:04 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 15:39:05 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_bonus.h"

/**========================================================================
 *                           ADD_VECTOR
 *========================================================================**/
void	add_vector(double a[], double b[], double sum_vect[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		sum_vect[i] = a[i] + b[i];
}

/**========================================================================
 *                           SUBTRACT_VECTOR
 *========================================================================**/
void	subtract_vector(double a[], double b[], double subt_vect[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		subt_vect[i] = a[i] - b[i];
}

/**========================================================================
 *                           SCALE_VECTOR
 *========================================================================**/
void	scale_vector(double vect[], double scaler, double scaled_vect[])
{
	int	i;

	i = -1;
	while (++i < AXIS)
		scaled_vect[i] = vect[i] * scaler;
}

/**========================================================================
 *                           SCALAR_PRODUCT
 *========================================================================**/
double	scalar_product(double a[], double b[])
{
	double	scalar;	
	int		i;

	scalar = 0.0;
	i = -1;
	while (++i < AXIS)
		scalar += a[i] * b[i];
	return (scalar);
}

/**========================================================================
 *                           CROSS_PRODUCT
 *========================================================================**/
void	cross_product(double a[], double b[], double cross_product[])
{
	cross_product[0] = a[1] * b[2] - a[2] * b[1];
	cross_product[1] = a[2] * b[0] - a[0] * b[2];
	cross_product[2] = a[0] * b[1] - a[1] * b[0];
}
