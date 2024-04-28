/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansylvain <dansylvain@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:32:59 by dansylvain        #+#    #+#             */
/*   Updated: 2024/04/28 14:34:24 by dansylvain       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	handle_last_token(char **token_end, char **last_token)
{
	**token_end = '\0';
	*last_token = *token_end + 1;
}

int	check_token_start(char *token_start, char *str_copy, char **last_token)
{
	if (*token_start == '\0')
	{
		free(str_copy);
		*last_token = NULL;
		return (0);
	}
	return (1);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_token = NULL;
	char		*token_start;
	char		*token_end;
	char		*str_copy;

	if (str != NULL)
		last_token = str;
	if (last_token == NULL || *last_token == '\0')
		return (NULL);
	str_copy = ft_strdup(last_token);
	if (str_copy == NULL)
		return (NULL);
	token_start = str_copy;
	while (*token_start != '\0' && ft_strchr(delim, *token_start) != NULL)
		token_start++;
	if (check_token_start(token_start, str_copy, &last_token) == 0)
		return (NULL);
	token_end = token_start + 1;
	while (*token_end != '\0' && ft_strchr(delim, *token_end) == NULL)
		token_end++;
	if (*token_end != '\0')
		handle_last_token(&token_end, &last_token);
	else
		last_token = NULL;
	return (token_start);
}
