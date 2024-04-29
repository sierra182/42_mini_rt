/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansylvain <dansylvain@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:24:27 by dansylvain        #+#    #+#             */
/*   Updated: 2024/04/29 18:24:30 by dansylvain       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	end_func(char **end, char **next_token)
{
	if (**end != '\0')
	{
		**end = '\0';
		*next_token = *end + 1;
	}
	else
		*next_token = NULL;
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next_token = NULL;
	char		*start;
	char		*end;

	if (str != NULL)
		next_token = str;
	else if (next_token == NULL)
		return (NULL);
	start = next_token;
	end = start;
	while (*start != '\0' && ft_strchr(delim, *start) != NULL)
		start++;
	if (*start == '\0')
	{
		next_token = NULL;
		return (NULL);
	}
	end = start;
	while (*end != '\0' && ft_strchr(delim, *end) == NULL)
		end++;
	end_func(&end, &next_token);
	return (start);
}
