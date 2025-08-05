#include "commons.h"

/**
 * @brief Safe close a file descriptor function from a file struct
 * 
 * @param file 
 */
void	safe_close(t_file *file)
{
	if (!file)
		return ;
	if (file->fd > 2)
	{
		close(file->fd);
		file->fd = -1;
	}
}

/**
* @brief Safe return function
* 
* @param context 
* @param status 
* @return int 
 */
int	safe_return(t_nm_context *context, int status)
{
	ft_flclear(&context->files, fldelete);
	return (status);
}
