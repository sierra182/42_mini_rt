/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:11:11 by seblin            #+#    #+#             */
/*   Updated: 2024/01/23 13:02:27 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

void	init_matrix(double matrix[][MTX])
{
	int	i;
	int	j;

	i = -1;
	while (++i < MTX)
	{
		matrix[i][i] = 1.0;
		j = -1;
		while (++j < MTX)
			if (i != j)
				matrix[i][j] = 0.0;
	}
}

static void	reset_matrix(t_point **pt_arr)
{
	int	i;

	while (*pt_arr)
	{
		i = 0;
		while (i < MTX)
			(*pt_arr)->new_vect[i++] = 0.0;
		pt_arr++;
	}
}

void	apply_matrix(double matrix[][MTX], t_point **pt_arr)
{
	int	i;
	int	j;

	reset_matrix(pt_arr);
	while (*pt_arr)
	{
		i = -1;
		while (++i < MTX)
		{
			j = -1;
			while (++j < MTX)
				(*pt_arr)->new_vect[i] += (int)(matrix[i][j]
						* (*pt_arr)->init_vect[j]);
		}
		pt_arr++;
	}
}

static double	multiply_rowbycol(double row[], double m2[][MTX], int col)
{
	double	rslt;
	int		i;

	rslt = 0;
	i = -1;
	while (++i < MTX)
		rslt += row[i] * m2[i][col];
	return (rslt);
}

void	multiply_matrix(double m1[][MTX], double m2[][MTX], double mf[][MTX])
{
	int	i;
	int	j;

	i = -1;
	while (++i < MTX)
	{
		j = -1;
		while (++j < MTX)
			mf[i][j] = multiply_rowbycol(m1[i], m2, j);
	}
}
