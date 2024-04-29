/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansylvain <dansylvain@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:22:21 by dansylvain        #+#    #+#             */
/*   Updated: 2024/04/29 18:22:33 by dansylvain       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	func_part_one(char **str, int *sign, double *result)
{
	while (**str == ' ')
		(*str)++;
	if (**str == '-')
	{
		*sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	while (ft_isdigit(**str))
	{
		*result = *result * 10.0 + (**str - '0');
		(*str)++;
	}
}

void	func_part_three(char **str, double *result)
{
	int	exponent;
	int	exp_sign;

	exponent = 0;
	if (**str == 'e' || **str == 'E')
	{
		(*str)++;
		exp_sign = 1;
		if (**str == '-')
		{
			exp_sign = -1;
			(*str)++;
		}
		else if (**str == '+')
			(*str)++;
		while (ft_isdigit(**str))
		{
			exponent = exponent * 10 + (**str - '0');
			(*str)++;
		}
		exponent *= exp_sign;
	}
	if (exponent != 0)
		*result *= pow(10, exponent);
}

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int		sign;
	double	divisor;

	result = 0.0;
	fraction = 0.0;
	sign = 1;
	func_part_one(&str, &sign, &result);
	result += fraction;
	if (*str == '.')
	{
		str++;
		divisor = 10.0;
		while (ft_isdigit(*str))
		{
			fraction += (*str - '0') / divisor;
			divisor *= 10.0;
			str++;
		}
	}
	func_part_three(&str, &result);
	return (result * sign);
}
