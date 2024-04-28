#include <unistd.h>
#include <stdio.h>

/**========================================================================
 *                           display_error
 *========================================================================**/
void	display_error(void)
{
	if (write(2, "Error\n", 6) < 0)
		perror("display_error\n");
}