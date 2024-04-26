/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:25:15 by svidot            #+#    #+#             */
/*   Updated: 2023/10/12 20:15:17 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c_uc;

	c_uc = (unsigned char) c;
	while (*s)
		if (*s++ == c_uc)
			return ((char *)--s);
	if (c_uc == '\0')
		return ((char *) s);
	return (NULL);
}
