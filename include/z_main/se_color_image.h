/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_color_image.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:55:11 by svidot            #+#    #+#             */
/*   Updated: 2024/06/26 12:55:12 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SE_COLOR_IMAGE_H
# define SE_COLOR_IMAGE_H

typedef struct s_color
{
	int	rgb[AXIS];
}	t_color;

typedef struct s_img
{
	void			*img_ptr;
	char			*img_data;
	int				line_len;
	int				bpp;
	unsigned int	alpha_color;
}	t_img;

typedef struct s_img_items
{
	t_img	legend;
	t_img	logo;
	t_img	sph;
	t_img	cam;
	t_img	bulb;
	t_img	amb;	
}	t_img_items;

#endif