# include "x_mini_struct.h"
# include "mlx.h"
# include "libft.h"

/**========================================================================
 *                           SECTION HEADER
 *========================================================================**/
void	chang_mech_size(t_data *data, int keycode)
{
	t_event *mesh;
	mesh = &data->event;

	if (keycode == PLUS)
	{
		if (mesh->actual_mesh.type == O_SP)
		{
			printf("sphere PLUS: %f\n", (((t_sphere *) mesh->actual_mesh.ref)->diameter));
			((t_sphere *) mesh->actual_mesh.ref)->diameter += 1;
			((t_sphere *) mesh->actual_mesh.ref)->square_radius = ((t_sphere *) mesh->actual_mesh.ref)->diameter / 2 * ((t_sphere *) mesh->actual_mesh.ref)->diameter / 2;
		}
		else if (mesh->actual_mesh.type == O_CY && mesh->ctrl_ispressed)
		{

			printf("cylinder PLUS: %f\n", (((t_cylinder *) mesh->actual_mesh.ref)->diameter));
			((t_cylinder *) mesh->actual_mesh.ref)->height += 1;
		}
		else if (mesh->actual_mesh.type == O_CY)
		{
			printf("cylinder PLUS: %f\n", (((t_cylinder *)  mesh->actual_mesh.ref)->diameter));
			((t_cylinder *) mesh->actual_mesh.ref)->diameter += 1;
			((t_cylinder *) mesh->actual_mesh.ref)->square_radius = ((t_cylinder *) mesh->actual_mesh.ref)->diameter / 2 * ((t_cylinder *) mesh->actual_mesh.ref)->diameter / 2;
			((t_cylinder *) mesh->actual_mesh.ref)->radius = ((t_cylinder *) mesh->actual_mesh.ref)->diameter / 2;

		}
	}
	else if  (keycode == MINUS)
	{
		if (mesh->actual_mesh.type == O_SP && ((t_sphere *) mesh->actual_mesh.ref)->diameter > 1)
		{
			printf("sphere MINUS: %f\n", (((t_sphere *) mesh->actual_mesh.ref)->diameter));
			((t_sphere *) mesh->actual_mesh.ref)->diameter -= 1;
			((t_sphere *) mesh->actual_mesh.ref)->square_radius = ((t_sphere *) mesh->actual_mesh.ref)->diameter / 2 * ((t_sphere *) mesh->actual_mesh.ref)->diameter / 2;
		}
		else if (mesh->actual_mesh.type == O_CY && mesh->ctrl_ispressed && ((t_cylinder *) mesh->actual_mesh.ref)->height > 1)
		{
			printf("cylinder MINUS + CTRL: %f\n", (((t_cylinder *)  mesh->actual_mesh.ref)->diameter));
			((t_cylinder *) mesh->actual_mesh.ref)->height -= 1;
		}
		else if (mesh->actual_mesh.type == O_CY && ((t_cylinder *) mesh->actual_mesh.ref)->diameter > 1)
		{
			printf("cylinder MINUS: %f\n", (((t_cylinder *)  mesh->actual_mesh.ref)->diameter));
			((t_cylinder *) mesh->actual_mesh.ref)->diameter -= 1;
			((t_cylinder *) mesh->actual_mesh.ref)->square_radius = ((t_cylinder *) mesh->actual_mesh.ref)->diameter / 2 * ((t_cylinder *) mesh->actual_mesh.ref)->diameter / 2;
			((t_cylinder *) mesh->actual_mesh.ref)->radius = ((t_cylinder *) mesh->actual_mesh.ref)->diameter / 2;

		}
	}
}