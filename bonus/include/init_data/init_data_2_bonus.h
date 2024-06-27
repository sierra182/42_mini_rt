/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_2_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:17:09 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:17:10 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_DATA_2_BONUS_H
# define INIT_DATA_2_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "se_mini_struct_bonus.h"

int		is_valid_xpm(char *str);
void	handle_uv_modifs_params(t_data *data, double *nbr, char *token, int *j);

#endif