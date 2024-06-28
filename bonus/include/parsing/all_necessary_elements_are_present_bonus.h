/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_necessary_elements_are_present_bonus.h         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:28:33 by svidot            #+#    #+#             */
/*   Updated: 2024/06/28 07:21:11 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_NECESSARY_ELEMENTS_ARE_PRESENT_BONUS_H
# define ALL_NECESSARY_ELEMENTS_ARE_PRESENT_BONUS_H

# define FILE_SIZE 1024000

# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "se_mini_struct_bonus.h"

int	element_is_present(char file_content[], char *el);

#endif