/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_exit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:48:14 by svidot            #+#    #+#             */
/*   Updated: 2024/04/26 16:59:03 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef X_EXIT_H
# define X_EXIT_H

# include "x_mini_struct.h"

void	add_exit_struct(void *ptr, t_enum_exit ex_en);
void	flush_exit_struct(void);
t_mlx	*get_mlx(void);

#endif