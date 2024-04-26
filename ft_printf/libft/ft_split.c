/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:54:21 by svidot            #+#    #+#             */
/*   Updated: 2024/01/08 11:35:21 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static char	**ft_assin_word(char **split, int word, char const *s, char c)
{
	char	**split2;
	size_t	let;
	size_t	i;

	split2 = split;
	while (*s)
	{
		let = 0;
		while (s[let] && s[let] != c)
			let++;
		if (let)
		{
			*split++ = (char *) ft_calloc((let + 1), sizeof (char));
			if (!*(split - 1))
			{
				ft_free_split(split2);
				return (NULL);
			}
		}
		i = 0;
		while ((*s++ && let--) || (i && !s--))
			(*(split - 1))[i++] = *(s - 1);
	}
	return (split - word);
}

char	**ft_split(char const *s, char c)
{
	char		**split;
	int			word;
	size_t		pass;
	size_t		i;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		pass = 0;
		while ((s[i] && s[i++] != c && ++pass) || (pass && word++ < 0))
			;
	}
	split = (char **) ft_calloc(word + 1, sizeof (char *));
	if (!split)
		return (NULL);
	return (ft_assin_word(split, word, s, c));
}
