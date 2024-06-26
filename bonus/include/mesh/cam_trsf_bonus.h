/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_trsf_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:27:50 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:44:17 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAM_TRSF_BONUS_H
# define CAM_TRSF_BONUS_H

# include "se_mini_struct_bonus.h"
# include "x_matrix_bonus.h"
# include "x_linear_algebra_bonus.h"

void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);

#endif