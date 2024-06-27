/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_data_are_valid_bonus.h                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:30:57 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:30:58 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_DATA_ARE_VALID_BONUS_H
# define ELEMENTS_DATA_ARE_VALID_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"

typedef enum t_num_type
{
	LTR,
	VECR,
	BYT,
	FOV,
	FL,
	UFL
}	t_num_type;

int		data_str_is_valid(char *str);
int		is_empty_str(char *str);
int		chck_fl(char *str, t_num_type num);
int		chck_bt(char *str, t_num_type num);
int		check_data(char *token, char *check);
void	free_tab(char **num);
int		check_data_nbrs(char *token, char	**num, int *i);
int		file_exists(char *map_path);

#endif