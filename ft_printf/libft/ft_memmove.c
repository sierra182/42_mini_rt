/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:20:36 by svidot            #+#    #+#             */
/*   Updated: 2023/10/12 20:11:28 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_uc;
	unsigned char		*dest_uc;

	if (!dest && !src)
		return (NULL);
	if (n == 0)
		return (dest);
	src_uc = (const unsigned char *) src;
	dest_uc = (unsigned char *) dest;
	if (src >= dest)
		while (n--)
			*dest_uc++ = *src_uc++;
	else
		while (n--)
			dest_uc[n] = src_uc[n];
	return (dest);
}
