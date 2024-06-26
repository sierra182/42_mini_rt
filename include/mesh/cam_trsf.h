/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_trsf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:50:26 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:50:27 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAM_TRSF_H
# define CAM_TRSF_H

# include "se_mini_struct.h"
# include "x_matrix.h"
# include "x_linear_algebra.h"

void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[]);

#endif