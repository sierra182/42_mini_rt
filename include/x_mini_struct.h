
#ifndef X_MINI_STRUCT_H
# define X_MINI_STRUCT_H

# define WIDTH 600
# define HEIGHT 500

typedef struct s_mlx
{
	void	*connect;
	void	*window;
}	t_mlx;

typedef struct s_exit
{
	t_mlx	*mlx;
}	t_exit;

typedef enum e_exit
{
	STT,
	MLX,
	END
}	t_enum_exit;

#endif