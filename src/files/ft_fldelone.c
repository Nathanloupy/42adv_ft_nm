#include "ft_nm.h"

void	ft_fldelone(t_file *file, void (*del)(void*))
{
	if (!file || !del)
		return ;
	del(file);
	free(file);
}
