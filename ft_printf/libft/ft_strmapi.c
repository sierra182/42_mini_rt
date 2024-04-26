/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:46:07 by svidot            #+#    #+#             */
/*   Updated: 2023/10/09 18:35:13 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	unsigned int	i;
	char			*s_new;
	size_t			s_len;

	s_len = ft_strlen(s);
	s_new = (char *) malloc(sizeof (char) * (s_len + 1));
	if (!s_new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		s_new[i] = f(i, s[i]);
		i++;
	}
	s_new[i] = '\0';
	return (s_new);
}
