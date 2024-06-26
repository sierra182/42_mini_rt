/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:17:34 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:18:20 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_DATA_BONUS_H
# define INIT_DATA_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "se_mini_struct_bonus.h"

void	fill_struct_a(t_data *data, double tab[]);
void	fill_struct_c(t_data *data, double tab[]);
void	fill_struct_l(t_data *data, double tab[]);
void	fill_struct_cy(t_data *data, double tab[]);
void	fill_struct_pl(t_data *data, double tab[]);
void	fill_struct_sp(t_data *data, double tab[]);
void	fill_struct_tr(t_data *data, double tab[]);
void	fill_struct_l_one(t_data *data, double tab[]);
int		create_data_structs(t_data *data);
double	*fill_tab(t_data *data, char *str, double tab[]);
double	*get_element_data(t_data *data, char *map_path, double tab[], char *el);
int		element_is_present(char *map_path, char *el);
void	get_elements_number(t_data *data, char *map_path);
int		update_cam(t_cam *cam);
void	post_init_cam(t_cam *cam);
void	init_vars(t_data *data);
void	save_data(t_data *data);
void	alloc_bump_maps(t_data *data);

#endif