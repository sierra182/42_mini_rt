#include "x_mini_struct.h"
#include <stdio.h>

/* 
typedef struct s_cam
{
	double		fov;
	double		focal_len;
	double		scale;
	double		aspect;
	int			resol[2];	
	t_vector	origin_vect;
	t_vector	up_vect;
	t_vector	forward_vect;
	t_vector	right_vect;
}	t_cam;
 */

void	print_tab(double tab[], char *str);


void	fill_struct_A(t_data data, double tab[])
{
	int i;

	i = 0;
	printf("A:\n");
	while (tab[i] != 1024)
	{
		if (i == 0)
			printf("%i: %f\n", i, tab[i]);
		if (i == 1)
			printf("%i: %f\n", i, tab[i]);
		if (i == 2)
			printf("%i: %f\n", i, tab[i]);
		if (i == 3)
			printf("%i: %f\n", i, tab[i]);
		i++;
	}}

void	fill_struct_C(t_data data, double tab[])
{
	int i;

	i = 0;
	printf("C:\n");
	while (tab[i] != 1024)
	{
		if (i == 0)
			printf("%i: %f\n", i, tab[i]);
		if (i == 1)
			printf("%i: %f\n", i, tab[i]);
		if (i == 2)
			printf("%i: %f\n", i, tab[i]);
		if (i == 3)
			printf("%i: %f\n", i, tab[i]);
		if (i == 4)
			printf("%i: %f\n", i, tab[i]);
		if (i == 5)
			printf("%i: %f\n", i, tab[i]);
		if (i == 6)
			printf("%i: %f\n", i, tab[i]);
		i++;
	}
}

void	fill_struct_L(t_data data, double tab[])
{
	int i;

	i = 0;
	printf("L:\n");
	while (tab[i] != 1024)
	{
		if (i == 0)
			printf("%i: %f\n", i, tab[i]);
		if (i == 1)
			printf("%i: %f\n", i, tab[i]);
		if (i == 2)
			printf("%i: %f\n", i, tab[i]);
		if (i == 3)
			printf("%i: %f\n", i, tab[i]);
		if (i == 4)
			printf("%i: %f\n", i, tab[i]);
		if (i == 5)
			printf("%i: %f\n", i, tab[i]);
		if (i == 6)
			printf("%i: %f\n", i, tab[i]);
		i++;
	}
}

int	create_and_fill_struct_cy(t_data data, double tab[])
{
	int i;

	i = 0;
	printf("cy:\n");
	while (tab[i] != 1024)
	{
		if (i == 0)
			printf("%i: %f\n", i, tab[i]);
		if (i == 1)
			printf("%i: %f\n", i, tab[i]);
		if (i == 2)
			printf("%i: %f\n", i, tab[i]);
		if (i == 3)
			printf("%i: %f\n", i, tab[i]);
		if (i == 4)
			printf("%i: %f\n", i, tab[i]);
		if (i == 5)
			printf("%i: %f\n", i, tab[i]);
		if (i == 6)
			printf("%i: %f\n", i, tab[i]);
		if (i == 7)
			printf("%i: %f\n", i, tab[i]);
		if (i == 8)
			printf("%i: %f\n", i, tab[i]);
		if (i == 9)
			printf("%i: %f\n", i, tab[i]);
		if (i == 10)
			printf("%i: %f\n", i, tab[i]);
		i++;
	}
	return (1);
}

int	create_and_fill_struct_pl(t_data data, double tab[])
{
	int i;

	i = 0;
	printf("pl:\n");
	while (tab[i] != 1024)
	{
		if (i == 0)
			printf("%i: %f\n", i, tab[i]);
		if (i == 1)
			printf("%i: %f\n", i, tab[i]);
		if (i == 2)
			printf("%i: %f\n", i, tab[i]);
		if (i == 3)
			printf("%i: %f\n", i, tab[i]);
		if (i == 4)
			printf("%i: %f\n", i, tab[i]);
		if (i == 5)
			printf("%i: %f\n", i, tab[i]);
		if (i == 6)
			printf("%i: %f\n", i, tab[i]);
		if (i == 7)
			printf("%i: %f\n", i, tab[i]);
		if (i == 8)
			printf("%i: %f\n", i, tab[i]);
		i++;
	}
	return (1);
}

int	create_and_fill_struct_sp(t_data data, double tab[])
{
	int i;

	i = 0;
	printf("sp:\n");
	while (tab[i] != 1024)
	{
		if (i == 0)
			printf("%i: %f\n", i, tab[i]);
		if (i == 1)
			printf("%i: %f\n", i, tab[i]);
		if (i == 2)
			printf("%i: %f\n", i, tab[i]);
		if (i == 3)
			printf("%i: %f\n", i, tab[i]);
		if (i == 4)
			printf("%i: %f\n", i, tab[i]);
		if (i == 5)
			printf("%i: %f\n", i, tab[i]);
		if (i == 6)
			printf("%i: %f\n", i, tab[i]);
		i++;
	}
	return (1);
}


void	print_tab(double tab[], char *str)
{
	int	i;

	printf("%s", str);
	i = 0;
	while (tab[i] != 1024)
		printf("%f\n", tab[i++]);
}