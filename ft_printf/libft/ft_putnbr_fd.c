/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:38:24 by svidot            #+#    #+#             */
/*   Updated: 2023/10/12 20:08:47 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	div;
	int	mod;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	else if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	div = n / 10;
	mod = n % 10;
	if (n > 9)
		ft_putnbr_fd(div, fd);
	ft_putchar_fd(mod + 48, fd);
}
