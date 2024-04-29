#include "exit.h"

t_exit	*get_exit_struct(void)
{
	static t_exit	exit;

	return (&exit);
}

static t_getsaf	*get_store_and_free(void)
{
	static void	(*store_and_free[END])(t_exit *, void *);

	if (!store_and_free[MLX])
	{
		store_and_free[MLX] = store_and_free_mlx;
	}
	return (store_and_free);
}

void	add_exit_struct(void *ptr, t_enum_exit ex_en)
{
	void	(**store_and_free)(t_exit *, void *);
	t_exit	*exit;

	exit = get_exit_struct();
	store_and_free = get_store_and_free();
	if (store_and_free[ex_en])
		store_and_free[ex_en](exit, ptr);
}

void	flush_exit_struct(void)
{
	void		(**store_and_free)(t_exit *, void *);
	t_enum_exit	ex_en;
	t_exit		*exit;

	ex_en = STT;
	exit = get_exit_struct();
	store_and_free = get_store_and_free();
	while (++ex_en < END)
		if (store_and_free[ex_en])
			store_and_free[ex_en](exit, NULL);
}
