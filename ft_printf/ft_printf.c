/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 08:04:59 by seblin            #+#    #+#             */
/*   Updated: 2023/12/21 17:05:42 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdarg.h> 
#include <stdint.h> 

static int	putnbr_base(uintptr_t n, unsigned int base, char casse, char pref)
{
	int	size;

	size = 0;
	if (pref == 'x' && ++size && size++)
		ft_putstr_fd("0x", 1);
	if (n >= base)
		size += putnbr_base(n / base, base, casse, 'z');
	if (n % base <= 9)
		ft_putchar_fd(n % base + 48, 1);
	else if (casse == 'u')
		ft_putchar_fd(n % base + 55, 1);
	else
		ft_putchar_fd(n % base + 87, 1);
	return (++size);
}

static void	manage_phlder_seq(const char *s, va_list lst, int *n_item, int *arg)
{
	long int	longarg;

	if ((*s == 'd' || *s == 'i') && ++(*n_item))
	{
		arg = &(int){va_arg(lst, int)};
		longarg = (long int) *arg;
		ft_putnbr_fd(*arg, 1);
		if (longarg < 0 && ++(*n_item))
			longarg = -longarg;
		while (longarg > 9 && ++(*n_item))
			longarg /= 10;
	}
	else if (*s == 'p')
	{
		arg = (int *) va_arg(lst, void *);
		if (!arg)
		{
			arg = (int *) "(nil)";
			ft_putstr_fd((char *) arg, 1);
			*n_item += 5;
		}
		else
			*n_item += putnbr_base((uintptr_t) arg, 16, 'l', 'x');
	}
}

static void	manage_phlder(const char *s, va_list lst, int *n_item)
{
	char	*arg;

	if (*s == '%' && ++(*n_item))
		ft_putchar_fd('%', 1);
	else if (*s == 'c' && ++(*n_item))
		ft_putchar_fd(va_arg(lst, int), 1);
	else if (*s == 's')
	{
		arg = va_arg(lst, char *);
		if (!arg)
			arg = "(null)";
		*n_item += ft_strlen(arg);
		ft_putstr_fd(arg, 1);
	}
	else if (*s == 'u')
		*n_item += putnbr_base(va_arg(lst, unsigned int), 10, 0, 0);
	else if (*s == 'x')
		*n_item += putnbr_base(va_arg(lst, unsigned int), 16, 'l', 0);
	else if (*s == 'X')
		*n_item += putnbr_base(va_arg(lst, unsigned int), 16, 'u', 0);
	manage_phlder_seq(s, lst, n_item, (int *) &arg);
}

int	ft_printf(const char *s, ...)
{
	va_list	lst;
	int		n_item;

	n_item = 0;
	va_start(lst, s);
	while (*s)
	{
		if (*s++ == '%')
			manage_phlder(s++, lst, &n_item);
		else if (++n_item)
			ft_putchar_fd(*(s - 1), 1);
	}
	va_end(lst);
	return (n_item);
}
