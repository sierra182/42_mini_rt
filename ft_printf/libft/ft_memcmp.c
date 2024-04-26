/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:51:19 by svidot            #+#    #+#             */
/*   Updated: 2023/10/17 22:04:33 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_uc;
	const unsigned char	*s2_uc;

	if (!n)
		return (0);
	s1_uc = (const unsigned char *) s1;
	s2_uc = (const unsigned char *) s2;
	while (--n && *s1_uc == *s2_uc)
	{
		s1_uc++;
		s2_uc++;
	}
	return ((const unsigned char) *s1_uc - (const unsigned char) *s2_uc);
}
