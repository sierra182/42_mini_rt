/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:09:16 by svidot            #+#    #+#             */
/*   Updated: 2023/10/09 08:33:24 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_uc;
	unsigned char		c_uc;

	s_uc = (const unsigned char *) s;
	c_uc = (unsigned char) c;
	while (n--)
		if (*s_uc++ == c_uc)
			return ((void *)--s_uc);
	return (NULL);
}
