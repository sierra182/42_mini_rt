/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keycode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:54:33 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:54:34 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_keycode.h"

/**========================================================================
 *                           CAM_EVENT_ROTATE
 *========================================================================**/
void	cam_event_rotate(int keycode, t_cam *cam)
{
	double	r;

	r = 1.0;
	if (keycode == R_LFT)
		rotate_cam(cam, r, (int []){0, 1, 0});
	else if (keycode == R_RGHT)
		rotate_cam(cam, -r, (int []){0, 1, 0});
	else if (keycode == R_UP)
		rotate_cam(cam, r, (int []){1, 0, 0});
	else if (keycode == R_DWN)
		rotate_cam(cam, -r, (int []){1, 0, 0});
	else if (keycode == S_LFT)
		rotate_cam(cam, r, (int []){0, 0, 1});
	else if (keycode == S_RGHT)
		rotate_cam(cam, -r, (int []){0, 0, 1});
}

/**========================================================================
 *                           EVENT_ROTATE
 *========================================================================**/
void	event_rotate(int keycode, t_matrix_vector *vector)
{
	double	r;

	r = 1.0;
	if (keycode == R_LFT)
		rotate_mesh(vector, r, (int []){1, 0, 0});
	else if (keycode == R_RGHT)
		rotate_mesh(vector, -r, (int []){1, 0, 0});
	else if (keycode == R_UP)
		rotate_mesh(vector, r, (int []){0, 1, 0});
	else if (keycode == R_DWN)
		rotate_mesh(vector, -r, (int []){0, 1, 0});
	else if (keycode == S_LFT)
		rotate_mesh(vector, r, (int []){0, 0, 1});
	else if (keycode == S_RGHT)
		rotate_mesh(vector, -r, (int []){0, 0, 1});
}

/**========================================================================
 *                           EVENT_TRANSLATE
 *========================================================================**/
void	event_translate(int keycode,
	void (*trsl_mesh)(t_cam *cam, t_matrix_vector *vect, double values[]),
		t_cam *cam, t_matrix_vector *vect)
{
	double	t;

	t = 1;
	if (keycode == UP)
		trsl_mesh(cam, vect, (double []){0.0, t, 0.0});
	else if (keycode == DWN)
		trsl_mesh(cam, vect, (double []){0.0, -t, 0.0});
	else if (keycode == LFT)
		trsl_mesh(cam, vect, (double []){t, 0.0, 0.0});
	else if (keycode == RGHT)
		trsl_mesh(cam, vect, (double []){-t, 0.0, 0.0});
	else if (keycode == FWRD)
		trsl_mesh(cam, vect, (double []){0.0, 0.0, t});
	else if (keycode == BACK)
		trsl_mesh(cam, vect, (double []){0.0, 0.0, -t});
}
