# include "x_mini_struct.h"
# include "mlx.h"
# include "libft.h"

void	handle_plus_key(t_data *data, int keycode)
{
	t_event *mesh;
	t_sphere	*sphere;
	t_cylinder	*cyl;

	mesh = &data->event;
	sphere = ((t_sphere *)mesh->actual_mesh.ref);
	cyl = ((t_cylinder *)mesh->actual_mesh.ref);
	if (mesh->actual_mesh.type == O_SP)
	{
		sphere->diameter += 1;
		sphere->square_radius = sphere->diameter / 2 * sphere->diameter / 2;
	}
	else if (mesh->actual_mesh.type == O_CY && mesh->ctrl_ispressed)
		cyl->height += 1;
	else if (mesh->actual_mesh.type == O_CY && !mesh->ctrl_ispressed)
	{
		cyl->diameter += 1;
		cyl->square_radius = cyl->diameter / 2 * cyl->diameter / 2;
		cyl->radius = cyl->diameter / 2;
	}
}

void	handle_minus_key(t_data *data, int keycode)
{
	t_event *mesh;
	t_sphere	*sphere;
	t_cylinder	*cyl;

	mesh = &data->event;
	sphere = ((t_sphere *)mesh->actual_mesh.ref);
	cyl = ((t_cylinder *)mesh->actual_mesh.ref);
	if (mesh->actual_mesh.type == O_SP && sphere->diameter > 1)
	{
		sphere->diameter -= 1;
		sphere->square_radius = sphere->diameter / 2 * sphere->diameter / 2;
	}
	else if (mesh->actual_mesh.type == O_CY && mesh->ctrl_ispressed && cyl->height > 1)
		cyl->height -= 1;
	else if (mesh->actual_mesh.type == O_CY && !mesh->ctrl_ispressed && cyl->diameter > 1)
	{
		cyl->diameter -= 1;
		cyl->square_radius = cyl->diameter / 2 * cyl->diameter / 2;
		cyl->radius = cyl->diameter / 2;
	}
}

/**========================================================================
 *                           SECTION HEADER
 *========================================================================**/
void	chang_mech_size(t_data *data, int keycode)
{
	if (keycode == PLUS)
		handle_plus_key(data, keycode);
	else if  (keycode == MINUS)
	{
		handle_minus_key(data, keycode);

		
	}
}