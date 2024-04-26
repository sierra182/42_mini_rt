/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:21:10 by svidot            #+#    #+#             */
/*   Updated: 2023/10/13 14:59:05 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_strndup(const char *s, size_t n)
{
	char	*s2;
	size_t	s_len;
	size_t	size;

	s_len = ft_strlen(s);
	if (n > s_len)
		size = s_len;
	else
		size = n;
	s2 = (char *) ft_calloc(size + 1, sizeof (char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s, size + 1);
	return (s2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	while (s1_len)
	{
		i = 0;
		while (set[i] && s1[s1_len - 1] != set[i])
			i++;
		if (!set[i])
			break ;
		s1_len--;
	}
	while (*s1 && s1_len)
	{
		i = 0;
		while (set[i] && *s1 != set[i])
			i++;
		if (!set[i])
			break ;
		s1_len--;
		s1++;
	}
	return (ft_strndup(s1, s1_len));
}
