#include "x_mini_struct.h"
#include "mlx.h"
#include "libft.h"


/**========================================================================
 *							HANDLE_PLUS_KEY
 * @brief 
 * 
 * @param data 
 * @param keycode 
========================================================================**/
void	handle_plus_key(t_data *data, int keycode)
{
	t_event		*mesh;
	t_sphere	*sphere;
	t_cylinder	*cyl;
	t_obj		obj;

	mesh = &data->event;
	obj = mesh->actual_mesh;
	sphere = ((t_sphere *)obj.ref);
	cyl = ((t_cylinder *)obj.ref);
	if (obj.type == O_SP)
	{
		sphere->diameter += 1;
		sphere->square_radius = pow(sphere->diameter / 2, 2);
	}
	else if (obj.type == O_CY && mesh->ctrl_ispressed)
		cyl->height += 1;
	else if (obj.type == O_CY && !mesh->ctrl_ispressed)
	{
		cyl->diameter += 1;
		cyl->square_radius = pow(cyl->diameter / 2, 2);
		cyl->radius = cyl->diameter / 2;
	}
}

/**========================================================================
 * 							HANDLE_MINUS_KEY
 * @brief 
 * 
 * @param data 
 * @param keycode 
========================================================================**/
void	handle_minus_key(t_data *data, int keycode)
{
	t_event		*mesh;
	t_sphere	*sphere;
	t_cylinder	*cyl;
	t_obj		obj;

	mesh = &data->event;
	obj = mesh->actual_mesh;
	sphere = ((t_sphere *)obj.ref);
	cyl = ((t_cylinder *)obj.ref);
	if (obj.type == O_SP && sphere->diameter > 1)
	{
		sphere->diameter -= 1;
		sphere->square_radius = pow(sphere->diameter / 2, 2);
	}
	else if (obj.type == O_CY && mesh->ctrl_ispressed && cyl->height > 1)
		cyl->height -= 1;
	else if (obj.type == O_CY && !mesh->ctrl_ispressed && cyl->diameter > 1)
	{
		cyl->diameter -= 1;
		cyl->square_radius = pow(cyl->diameter / 2, 2);
		cyl->radius = cyl->diameter / 2;
	}
}

/**========================================================================
 *                           CHANG_MECH_SIZE
 * @brief 
 * 
 * @param data 
 * @param keycode 
========================================================================**/
void	chang_mech_size(t_data *data, int keycode)
{
	if (keycode == PLUS)
		handle_plus_key(data, keycode);
	else if (keycode == MINUS)
	{
		handle_minus_key(data, keycode);
	}
}
