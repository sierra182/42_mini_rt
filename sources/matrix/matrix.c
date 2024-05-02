# define MTX 4

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