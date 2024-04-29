#include <stddef.h>
#include <stdbool.h>
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

char *ft_strtok(char *str, const char *delim)
{
    static char *next_token;
    char *start;
    char *end;

	next_token = NULL;
    if (str != NULL)
        next_token = str;
	else if (next_token == NULL)
        return NULL;
	start = next_token;
	end = start;	
    while (*start != '\0' && ft_strchr(delim, *start) != NULL)
        start++;
    if (*start == '\0')
	{
        next_token = NULL;
        return NULL;
    }
    end = start;
    while (*end != '\0' && ft_strchr(delim, *end) == NULL)
		end++;
	end_func(&end, &next_token);
    return start;
}
