/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:35:46 by seblin            #+#    #+#             */
/*   Updated: 2024/04/26 16:21:41 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <stdlib.h>
# include "x_mini_struct.h"

typedef void	(*t_getsaf)(t_exit *, void *);
void			store_and_free_mlx(t_exit *exit, void *mlx);

#endif