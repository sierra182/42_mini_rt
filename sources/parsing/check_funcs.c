#include "check_funcs.h"

/**========================================================================
 *                           TYP_CHECK_FL
 *========================================================================**/
int	typ_check_fl(char *str, t_num_type num)
{
	float	tmp;

	tmp = ft_atof(str);
	if (num == LTR)
	{
		if (tmp < 0.0 || tmp > 1.0)
			return (0);
	}
	else if (num == VECR)
	{
		if (tmp < -1.0 || tmp > 1.0)
			return (0);
	}
	else if (num == UFL)
	{
		if (tmp < 0.0)
			return (0);
	}
	return (1);
}

/**========================================================================
 *                           TYP_CHECK_BT
 *========================================================================**/
int	typ_check_bt(char *str, t_num_type num)
{
	int	tmp;

	tmp = ft_atoi(str);
	if (num == BYT)
	{
		if (tmp < 0 || tmp > 255)
			return (0);
	}
	else if (num == FOV)
	{
		if (tmp < 0 || tmp > 180)
			return (0);
	}
	return (1);
}

/**========================================================================
 *                           CHCK_FL
 * validity of floats check based on strlen: must be < 10
 *? Should I use overflow? 
 *========================================================================**/
int	chck_fl(char *str, t_num_type num)
{
	int	i;
	int	n;

	if (str == NULL)
		return (1);
	if (ft_strlen(str) > 100)
		return (0);
	if (!str[0] || (str[0] != '-' && str[0] != '+' && !ft_isdigit(str[0])))
		return (0);
	i = 1;
	n = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (str[i] == '.')
			n++;
		if ((!ft_isdigit(str[i]) && str[i] != '.')
			|| str[i] == '-' || str[i] == '+')
			return (0);
		i++;
	}
	i--;
	if (!ft_isdigit(str[i]) || n > 1 || typ_check_fl(str, num) == 0)
		return (0);
	return (1);
}

/**========================================================================
 *                           CHCK_BT
 *========================================================================**/
int	chck_bt(char *str, t_num_type num)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	if (ft_strlen(str) > 4 || (ft_strlen(str) > 3 && str[0] != '+'))
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '+')
			return (0);
		i++;
	}
	if (typ_check_bt(str, num) == 0)
		return (0);
	return (1);
}
