/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_funcs_2_bonus.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:15:06 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:15:07 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_STRUCT_FUNCS_2_BONUS_H
# define FILL_STRUCT_FUNCS_2_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "se_mini_struct_bonus.h"

int		gray_to_hex_string(const char *gray_string, char *hex_output);
int		hex_to_int(const char *hex_string);
void	get_texture(t_data *data, int i);
char	*get_bmpath(t_data *data, int index);
void	handle_uv_modif_params(double nbr, t_data *data, int i);

#endif