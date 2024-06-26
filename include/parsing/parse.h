/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:51:20 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:58:15 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "se_mini_struct.h"

int	is_rt_file(char *map_path);
int	file_exists(char *map_path);
int	file_content_is_correct(char *map_path);

#endif