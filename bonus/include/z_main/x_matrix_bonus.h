/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_matrix_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:41:38 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:41:39 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef X_MATRIX_BONUS_H
# define X_MATRIX_BONUS_H

# include "se_mini_struct_bonus.h"

void	init_matrix(t_matrix_vector matrix[]);
void	multiply_matrix(t_matrix_vector a[], t_matrix_vector b[],
			t_matrix_vector mult_matrix[]);
void	apply_matrix(t_matrix_vector matrix[], t_matrix_vector *vector,
			t_matrix_vector *applied_vect);
void	set_matrix_translate(t_matrix_vector matrix[], double trans[]);
void	set_matrix_scale(double matrix[][AXIS], double scale[]);
void	set_matrix_rotation(t_matrix_vector matrix[], double angle, int axe[]);

#endif