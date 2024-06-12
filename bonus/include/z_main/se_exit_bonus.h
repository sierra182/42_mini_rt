#ifndef SE_EXIT_H
# define SE_EXIT_H

# include "se_mini_struct_bonus.h"

typedef struct s_exit
{
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_plane		*planes;
	t_spotlight	*spotlights;
	t_mlx		*mlx;
	t_data		*data_cpy;
}	t_exit;

typedef enum e_exit
{
	STT,
	MLX,
	SP,
	CY,
	PL,
	SL,
	DATA,
	END
}	t_enum_exit;

void	add_exit_struct(void *ptr, t_enum_exit ex_en);
void	flush_exit_struct(void);
t_mlx	*get_mlx(void);

#endif