/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:31:34 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:31:40 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "se_mini_struct_bonus.h"

int	is_rt_file(char *map_path);
int	file_exists(char *map_path);
int	file_content_is_correct(char *map_path);

#endif