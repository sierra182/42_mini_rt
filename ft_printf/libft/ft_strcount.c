/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:21:15 by dsylvain          #+#    #+#             */
/*   Updated: 2024/05/15 18:24:51 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcount(const char *haystack, const char *needle)
{
	size_t	count;
	size_t	needle_len;

	count = 0;
	needle_len = ft_strlen(needle);
	while (*haystack)
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
		{
			count++;
			haystack += needle_len;
		}
		else
			haystack++;
	}
	return (count);
}
