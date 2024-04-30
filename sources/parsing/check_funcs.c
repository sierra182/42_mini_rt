#include "check_file.h"

#include "ft_printf.h"
#include <stdio.h>

int	typ_check_fl(char *str, num_type num)
{
	float tmp;

	tmp = atof(str);
	// printf("string: %s, float: %f\n", str, tmp);
	if (num == LTR)
	{
		// printf("LTR: %f ", tmp);
		if (tmp < 0.0 || tmp > 1.0)
		{
			// printf("NONO!\n");
			return (0);
		}
	}
	else if (num == VECR)
	{
		// printf("VECR: %f ", tmp);
		if (tmp < -1.0 || tmp > 1.0)
		{
			// printf("NONO!\n");
			return (0);
		}
	}
	return (1);
}

int	typ_check_bt(char *str, num_type num)
{
	int tmp;

	tmp = ft_atoi(str);
	// printf("string: %s, float: %f\n", str, tmp);
	if (num == BYT)
	{
		// printf("BYT: %i ", tmp);
		if (tmp < 0 || tmp > 255)
		{
			// printf("NONO!\n");
			return (0);
		}
	}
	else if (num == FOV)
	{
		// printf("FOV: %i ", tmp);
		if (tmp < 0 || tmp > 180)
		{
			// printf("NONO!\n");
			return (0);
		}
	}
	return (1);
}

/**========================================================================
 *                           chck_fl
 *========================================================================**/
int	chck_fl(char *str, num_type num)
{
	int	i;
	int	n;

	if (str == NULL)
		return (1);
	if (ft_strlen(str) > 10)
		return (0);
	if (!str[0] || (str[0] != '-' && str[0] != '+' && !ft_isdigit(str[0])))
		return (0);
	i = 1;
	n = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (str[i] == '.')
			n++;
		if ((!ft_isdigit(str[i]) && str[i] != '.') || str[i] == '-' || str[i] == '+')
			return (0);
		i++;
	}
	i--;
	if (!ft_isdigit(str[i]) || n > 1)
		return (0);
	if (typ_check_fl(str, num) == 0)
		return (0);	
	return (1);
}

/**========================================================================
 *                           chck_bt
 *========================================================================**/
int	chck_bt(char *str, num_type num)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	if (ft_strlen(str) > 3)
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if(typ_check_bt(str, num) == 0)
		return (0);
	return (1);
}
