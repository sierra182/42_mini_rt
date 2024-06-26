/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_intersect.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:52:51 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:52:52 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTERSECT_H
# define IS_INTERSECT_H

# include "se_mini_struct.h"
# include "math.h"
# include "x_linear_algebra.h"

double	which_t(double eq_values[], int *which_t, double *tt[]);

# define EPSILON 1e-6

#endif