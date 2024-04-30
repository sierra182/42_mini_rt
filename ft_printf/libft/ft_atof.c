/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansylvain <dansylvain@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:22:21 by dansylvain        #+#    #+#             */
/*   Updated: 2024/04/30 11:09:03 by dansylvain       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	func_part_1(char **str, int *sign, double *result)
{
	while (**str == ' ')
		(*str)++;
	if (**str == '-')
	{
		*sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		str++;
	while (**str >= '0' && **str <= '9')
	{
		*result = *result * 10.0 + (**str - '0');
		(*str)++;
	}
}

void	func_part_2(char **str, double *fraction, int *divisor)
{
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			*fraction = *fraction + (**str - '0') / (double)(*divisor);
			*divisor *= 10;
			(*str)++;
		}
	}
}

void	func_part_3(char **str, int *exponent)
{
	int	exp_sign;

	exp_sign = 1;
	if (**str == 'e' || **str == 'E')
	{
		(*str)++;
		if (**str == '-')
		{
			exp_sign = -1;
			(*str)++;
		}
		else if (**str == '+')
			(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			*exponent = *exponent * 10 + (**str - '0');
			(*str)++;
		}
		*exponent *= exp_sign;
	}
}

void	func_part_4(double *result, int sign, double fraction, int *exponent)
{
	double	power;

	*result = sign * (*result + fraction);
	if (*exponent != 0)
	{
		power = 10.0;
		while (*exponent > 1)
		{
			power *= 10.0;
			(*exponent)--;
		}
		while (*exponent < -1)
		{
			power /= 10.0;
			(*exponent)++;
		}
		*result *= power;
	}
}

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		exponent;
	int		divisor;

	result = 0.0;
	fraction = 0.0;
	sign = 1;
	exponent = 0;
	divisor = 10;
	func_part_1(&str, &sign, &result);
	func_part_2(&str, &fraction, &divisor);
	func_part_3(&str, &exponent);
	func_part_4(&result, sign, fraction, &exponent);
	return (result);
}
