/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_is_correct.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:51:14 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:10:54 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_CONTENT_IS_CORRECT_H
# define FILE_CONTENT_IS_CORRECT_H

# define FILE_SIZE 1024000

# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "se_mini_struct.h"

int	all_necessary_elements_are_present(char file_content[]);
int	elements_data_are_valid(char *map_path);
int	is_only_valid_chars(char file_content[]);
int	is_valid_char(char c);

#endif