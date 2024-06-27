/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_funcs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:50:55 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:58:59 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_FUNCS_H
# define CHECK_FUNCS_H

# include <stdlib.h>
# include <unistd.h>
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

#endif