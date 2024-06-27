/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_intersect_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:36:19 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:36:36 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTERSECT_BONUS_H
# define IS_INTERSECT_BONUS_H

# define EPSILON 1e-6

# include <math.h>
# include "se_mini_struct_bonus.h"
# include "x_linear_algebra_bonus.h"

double	which_t(double eq_values[], int *which_t, double *tt[]);

#endif