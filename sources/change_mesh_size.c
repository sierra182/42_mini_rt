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
			printf("sphere PLUS\n");
		else if (mesh->actual_mesh.type == O_CY && mesh->ctrl_ispressed)
			printf("cylinder PLUS + CTRL\n");
		else if (mesh->actual_mesh.type == O_CY)
			printf("cylinder PLUS\n");
	}
	else if  (keycode == MINUS)
	{
		if (mesh->actual_mesh.type == O_SP)
			printf("sphere MINUS\n");
		else if (mesh->actual_mesh.type == O_CY && mesh->ctrl_ispressed)
			printf("cylinder MINUS + CTRL\n");
		else if (mesh->actual_mesh.type == O_CY)
			printf("cylinder MINUS\n");
	}
}