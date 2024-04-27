/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_overflow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:29:20 by seblin            #+#    #+#             */
/*   Updated: 2024/04/27 17:30:30 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"

int	ft_isoverflow(char *str)
{
	long	nbr;
	int		isneg;

	nbr = 0;
	isneg = 0;
	if (*str == '-' && ++isneg)
		str++;
	else if (*str == '+')
		str++;
	while (*str)
	{
		nbr = nbr * 10 + *str++ - 48;
		if (nbr - isneg > INT_MAX)
			return (1);
	}
	return (0);
}
