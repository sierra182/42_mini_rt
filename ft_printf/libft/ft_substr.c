/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:55:53 by svidot            #+#    #+#             */
/*   Updated: 2023/10/12 20:13:34 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;
	size_t	s_len;
	size_t	malloc_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		malloc_len = 0;
	else if (start + len > s_len)
		malloc_len = s_len - start;
	else
		malloc_len = len;
	sub_s = (char *) malloc(sizeof (char) * (malloc_len + 1));
	if (!sub_s)
		return (NULL);
	i = 0;
	while (start < s_len && i < len && s[start + i])
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
