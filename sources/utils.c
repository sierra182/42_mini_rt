#include <unistd.h>
#include <stdio.h>
#include "libft.h"

/**========================================================================
 *                           display_error
 *========================================================================**/
void	display_error(char *str)
{
	printf("Error\n");
	if (write (2, str, ft_strlen(str)) == -1)
		perror("display_error");
}
