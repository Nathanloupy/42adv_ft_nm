#include "ft_nm.h"

/**
 * @brief Print the error corresponding to the error code to the standard error stream
 * 
 * @param arg 
 */
void	ft_nm_perror(char *arg)
{
	ft_putstr_fd(FT_NM_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	ft_nm_error_custom(char *arg, char *error_message)
{
	ft_putstr_fd(FT_NM_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	error_file_format(t_file *file)
{
	ft_nm_error_custom(file->filepath, FT_NM_FILE_FORMAT_ERROR);
	file->recoverable_error = 1;
	return (1);
}
