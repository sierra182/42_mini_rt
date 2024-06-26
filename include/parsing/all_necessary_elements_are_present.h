/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_necessary_elements_are_present.h               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:50:48 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:59:26 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_NECESSARY_ELEMENTS_ARE_PRESENT_H
# define ALL_NECESSARY_ELEMENTS_ARE_PRESENT_H
# define FILE_SIZE 1024

# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "se_mini_struct.h"

int	element_is_present(char file_content[], char *el);

#endif