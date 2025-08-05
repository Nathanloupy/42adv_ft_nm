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
	safe_close(file);
	file->filepath = NULL;
}
