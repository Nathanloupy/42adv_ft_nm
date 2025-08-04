#include "commons.h"

/**
 * @brief Print an error message to the standard error stream
 * 
 * @param function_name 
 */
void	ft_nm_perror(char *function_name)
{
	ft_putstr_fd(FT_NM_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (function_name)
	{
		ft_putstr_fd(function_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}