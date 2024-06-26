/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:14:35 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 13:14:36 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_BONUS_H
# define EXIT_BONUS_H

# include <stdlib.h>
# include "se_mini_struct_bonus.h"

typedef void	(*t_getsaf)(t_exit *, void *);
void			store_and_free_mlx(t_exit *exit, void *mlx);
void			store_and_free_spheres(t_exit *exit, void *spheres);
void			store_and_free_cylinders(t_exit *exit, void *cylinders);
void			store_and_free_planes(t_exit *exit, void *planes);
void			store_and_free_data_copy(t_exit *exit, void *data_cpy);
void			store_and_free_spotlights(t_exit *exit, void *spotlights);
void			store_and_free_triangles(t_exit *exit, void *triangles);

#endif