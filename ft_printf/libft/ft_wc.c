/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:11:08 by marvin            #+#    #+#             */
/*   Updated: 2023/11/18 17:11:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wc(char *s)
{
	int		flag;
	size_t	n_word;

	n_word = 0;
	while (s && *s)
	{
		flag = 0;
		while ((*s && !ft_isspace(*s++) && ++flag) || (flag && !++n_word))
			;
	}
	return (n_word);
}
