/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:43:02 by svidot            #+#    #+#             */
/*   Updated: 2023/10/09 08:15:31 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*s_dup;
	size_t	s_len;

	s_len = ft_strlen(s);
	s_dup = (char *) malloc(sizeof(char) * (s_len + 1));
	if (!s_dup)
		return (NULL);
	while (*s)
		*s_dup++ = *s++;
	*s_dup = '\0';
	return (s_dup - s_len);
}
