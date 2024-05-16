#include "all_necessary_elements_are_present.h"

/**========================================================================
 *                           all_necessary_elements_are_present
 * ! remove comment to enable element nbr check 
 *========================================================================**/
int	all_necessary_elements_are_present(t_data *data, char file_content[])
{
	if (element_is_present(file_content, "A") != 1)
	{
		int n = element_is_present(file_content, "A");
		printf("element_is_present 1, A: %i\n", n);
		return (0);
	}
	if (element_is_present(file_content, "C") != 1)
	{
		printf("element_is_present 2\n");
		return (0);
	}
	if (element_is_present(file_content, "L") != 1)
	{
		printf("element_is_present 3\n");
		return (0);
	}
	data->sp_nbr = element_is_present(file_content, "sp");
	if (data->sp_nbr == 0)
	{
		printf("element_is_present 4\n");
		return (0);
	}
	data->cy_nbr = element_is_present(file_content, "cy");
	if (data->cy_nbr == 0)
	{
		printf("element_is_present 5\n");
		return (0);
	}
	data->pl_nbr = element_is_present(file_content, "pl");
	if (data->pl_nbr == 0)
	{
		printf("element_is_present 6\n");
		return (0);
	}
	return (1);
}

/**========================================================================
 *                           element_is_present
 *========================================================================**/
int	element_is_present(char file_content[], char *el)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	n = ft_strcount(file_content, el);
	return (n);
}
