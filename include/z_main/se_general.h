/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_general.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:55:41 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:55:42 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SE_GENERAL_H
# define SE_GENERAL_H

typedef struct s_data	t_data;

typedef struct s_mlx
{
	void		*connect;
	void		*window;
	t_img		img;
	t_img_items	img_items;
}	t_mlx;

typedef enum e_obj_type
{
	O_SP,
	O_CY,
	O_PL
}	t_obj_type;

typedef struct s_obj_intersect
{
	double			t;
	enum e_obj_type	type;
	void			*ref;
}	t_obj;

#endif