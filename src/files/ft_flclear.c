#include "commons.h"

void	ft_flclear(t_file **file, void (*del)(void*))
{
	t_file	*tmp;

	if (!file || !del)
		return ;
	while (*file != NULL)
	{
		tmp = (*file)->next;
		ft_fldelone(*file, del);
		*file = tmp;
	}
	file = NULL;
}