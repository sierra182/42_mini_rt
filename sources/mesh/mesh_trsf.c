/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_trsf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:59:18 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:59:19 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_trsf.h"

/**========================================================================
 *                           TRSL_MESH
 *========================================================================**/
void	trsl_mesh(t_cam *cam, t_matrix_vector *vect, double values[])
{
	t_matrix_vector	applied_vect;
	t_matrix_vector	trsf_matrix[MTX];

	(void) cam;
	init_matrix(trsf_matrix);
	set_matrix_translate(trsf_matrix, values);
	apply_matrix(trsf_matrix, vect, &applied_vect);
	*vect = applied_vect;
}

/**========================================================================
 *                           ROTATE_MESH
 *========================================================================**/
void	rotate_mesh(t_matrix_vector *vect, double angle, int axe[])
{
	t_matrix_vector	trsf_matrix[MTX];
	t_matrix_vector	applied_vect;

	init_matrix(trsf_matrix);
	set_matrix_rotation(trsf_matrix, angle, axe);
	apply_matrix(trsf_matrix, vect, &applied_vect);
	*vect = applied_vect;
}
