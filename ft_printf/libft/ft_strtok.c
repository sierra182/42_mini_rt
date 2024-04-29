/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansylvain <dansylvain@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:32:59 by dansylvain        #+#    #+#             */
/*   Updated: 2024/04/29 14:11:51 by dansylvain       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include "libft.h"
char *ft_strtok(char *str, const char *delim) {
    static char *next_token = NULL;
    if (str != NULL) {
        next_token = str;
    } else if (next_token == NULL) {
        return NULL;
    }

    char *start = next_token;
    char *end = start;
    
    // Skip leading delimiters
    while (*start != '\0' && ft_strchr(delim, *start) != NULL) {
        start++;
    }

    // If we're at the end of the string, return NULL
    if (*start == '\0') {
        next_token = NULL;
        return NULL;
    }

    // Find the end of the token
    end = start;
    while (*end != '\0' && ft_strchr(delim, *end) == NULL) {
        end++;
    }

    // Set the next token to start after this one
    if (*end != '\0') {
        *end = '\0'; // Terminate the token
        next_token = end + 1;
    } else {
        next_token = NULL;
    }

    return start;
}

// #include "libft.h"
// #include <stdlib.h>

// void	handle_last_token(char **token_end, char **last_token)
// {
// 	**token_end = '\0';
// 	*last_token = *token_end + 1;
// }

// int	check_token_start(char *token_start, char *str_copy, char **last_token)
// {
// 	if (*token_start == '\0')
// 	{
// 		free(str_copy);
// 		*last_token = NULL;
// 		return (0);
// 	}
// 	return (1);
// }

// char	*ft_strtok(char *str, const char *delim)
// {
// 	static char	*last_token = NULL;
// 	char		*token_start;
// 	char		*token_end;
// 	char		*str_copy;

// 	if (str != NULL)
// 		last_token = str;
// 	if (last_token == NULL || *last_token == '\0')
// 		return (NULL);
// 	str_copy = ft_strdup(last_token);
// 	if (str_copy == NULL)
// 		return (NULL);
// 	token_start = str_copy;
// 	while (*token_start != '\0' && ft_strchr(delim, *token_start) != NULL)
// 		token_start++;
// 	if (check_token_start(token_start, str_copy, &last_token) == 0)
// 		return (NULL);
// 	token_end = token_start + 1;
// 	while (*token_end != '\0' && ft_strchr(delim, *token_end) == NULL)
// 		token_end++;
// 	if (*token_end != '\0')
// 		handle_last_token(&token_end, &last_token);
// 	else
// 		last_token = NULL;
// 	return (token_start);
// }
