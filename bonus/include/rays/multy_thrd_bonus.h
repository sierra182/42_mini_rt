/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multy_thrd_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:38:05 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:38:06 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTY_THRD_BONUS_H
# define MULTY_THRD_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include "libft.h"
# include "se_mini_struct_bonus.h"

typedef struct s_launch_rays
{
	int				i;
	int				j;
	int				k;
	int				x_stt;
	int				x_end;
	int				y_stt;
	int				y_end;
	pthread_t		tids[THR];
	t_multy_threads	multy[THR];
	t_data			data_copies[THR];
}	t_launch_rays;

void	*launch_rays(void *multy_input);
void	make_bin_file(t_data *data, t_mlx *mlx);

#endif