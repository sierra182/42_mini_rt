/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:15:20 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:16:06 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_TEXTURE_BONUS_H
# define GET_TEXTURE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "fill_struct_funcs_2_bonus.h"

int				gray_to_hex_string(const char *gray_string, char *hex_output);
int				hex_to_int(const char *hex_string);
void			get_texture(t_data *data, int i);
unsigned char	int_to_grayscale(unsigned int hex_value);
void			free_tab_bump(char **tab);
void			get_shades_nbr(t_sphere *sphere, int fd, int *shades_nbr,
					int *char_pp);
void			extract_texture_values(int shades_nbr, int char_pp, int fd,
					int int_tab[][2]);
void			fill_bump_map(t_fill_bump_map *p, int int_tab[][2]);
void			handle_line(t_handle_line_params *p, int int_tab[][2]);

#endif