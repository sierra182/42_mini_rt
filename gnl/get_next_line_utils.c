/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:14:05 by svidot            #+#    #+#             */
/*   Updated: 2024/03/15 11:32:42 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && *s++)
		i++;
	return (i);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*s2;
	size_t	s_len;
	size_t	size;
	size_t	size_save;

	s_len = ft_strlen(s);
	if (n > s_len)
		size = s_len;
	else
		size = n;
	size_save = size;
	s2 = (char *) malloc((size + 1) * sizeof (char));
	if (!s2)
		return (NULL);
	while (size--)
		*s2++ = *s++;
	*s2 = 0;
	return (s2 - size_save);
}

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

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			len;
	size_t			len_save;

	if (size && nmemb * size / size != nmemb)
		return (NULL);
	len = nmemb * size;
	len_save = len;
	ptr = (unsigned char *) malloc(len);
	if (!ptr)
		return (NULL);
	while (len--)
		*ptr++ = 0;
	return ((void *) ptr - len_save);
}

void	*free_buffer(char **buffer)
{
	if (*buffer)
		free(*buffer);
	*buffer = NULL;
	return (NULL);
}
