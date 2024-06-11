#include "parsing_utils_bonus.h"

/**========================================================================
 *                           DISPLAY_ERROR
 *========================================================================**/
void	display_error(char *str)
{
	printf("Error\n");
	if (write (2, str, ft_strlen(str)) == -1)
		perror("display_error");
}

/**========================================================================
 *                           WRITE_FD
 *========================================================================**/
void	write_fd(int fd, char *str)
{
	if (write (fd, str, ft_strlen(str)) == -1)
		perror("write_fd_error");
}
