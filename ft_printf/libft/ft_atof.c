/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansylvain <dansylvain@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:22:21 by dansylvain        #+#    #+#             */
/*   Updated: 2024/04/30 10:17:28 by dansylvain       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
#include <stdlib.h>

double ft_atof(char *str) {
    double result = 0.0;
    double fraction = 0.0;
    int sign = 1;
    int exponent = 0;
    int exp_sign = 1;
    int divisor = 10;

    // Skip leading whitespaces
    while (*str == ' ')
        str++;

    // Handle sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Parse integer part
    while (*str >= '0' && *str <= '9') {
        result = result * 10.0 + (*str - '0');
        str++;
    }

    // Parse fraction part
    if (*str == '.') {
        str++;
        while (*str >= '0' && *str <= '9') {
            fraction = fraction + (*str - '0') / (double)divisor;
            divisor *= 10;
            str++;
        }
    }

    // Parse exponent part
    if (*str == 'e' || *str == 'E') {
        str++;
        if (*str == '-') {
            exp_sign = -1;
            str++;
        } else if (*str == '+') {
            str++;
        }
        while (*str >= '0' && *str <= '9') {
            exponent = exponent * 10 + (*str - '0');
            str++;
        }
        exponent *= exp_sign;
    }

    // Combine integer and fraction parts
    result = sign * (result + fraction);

    // Adjust result based on exponent
    if (exponent != 0) {
        double power = 10.0;
        while (exponent > 1) {
            power *= 10.0;
            exponent--;
        }
        while (exponent < -1) {
            power /= 10.0;
            exponent++;
        }
        result *= power;
    }

    return result;
}
