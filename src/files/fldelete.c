#include "ft_nm.h"

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
	safe_cleanup_file(file);
	file->filepath = NULL;
}
