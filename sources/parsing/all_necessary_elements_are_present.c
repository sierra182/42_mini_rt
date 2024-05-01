#include "all_necessary_elements_are_present.h"
#include "x_mini_struct.h"

# define FILE_SIZE 1024


/**========================================================================
 *                           all_necessary_elements_are_present
 *========================================================================**/
int	all_necessary_elements_are_present(t_data *data, char file_content[])
{
	if (element_is_present(file_content, "A") != 1)
		return (0);
	if (element_is_present(file_content, "C") != 1)
		return (0);
	if (element_is_present(file_content, "L") != 1)
		return (0);
	data->sp_nbr = element_is_present(file_content, "sp");
	if (data->sp_nbr == 0)
		return (0);
	data->cy_nbr = element_is_present(file_content, "cy");
	if (data->cy_nbr == 0)
		return (0);
	data->pl_nbr = element_is_present(file_content, "pl");
	if (data->pl_nbr == 0)
		return (0);
	return (1);
}

#include <stdio.h>
/**========================================================================
 *                           element_is_present
 *========================================================================**/
int	element_is_present(char file_content[], char *el)
{
	int	i;
	int	n;

	n = 0;
	i = 0;

	

	while (i < FILE_SIZE)
	{
		if (!ft_strncmp(&file_content[i], el, ft_strlen(el))
			&& (!file_content[i + ft_strlen(el)] || ft_isspace(file_content
					[i + ft_strlen(el)])) && (i > 0 && (!file_content[i - 1]
				|| ft_isspace(file_content[i - 1]))))
			n++;
		i++;
	}
	return (n);
}
