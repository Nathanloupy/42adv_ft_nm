#include "commons.h"

/**
 * @brief Delete a file
 * 
 * @param data 
 */
void	fldelete(void *data)
{
	t_file	*file;

	if (!data)
		return ;
	file = (t_file *)data;
	if (file->fd > 2)
	{
		close(file->fd);
		file->fd = -1;
	}
	file->filepath = NULL;
}
