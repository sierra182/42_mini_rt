/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:00:30 by svidot            #+#    #+#             */
/*   Updated: 2023/10/12 20:11:07 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	c_uc;
	int				i;

	c_uc = (unsigned char) c;
	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
		if (s[i--] == c_uc)
			return ((char *) &s[++i]);
	return (NULL);
}
