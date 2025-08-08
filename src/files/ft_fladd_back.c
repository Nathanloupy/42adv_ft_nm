#include "ft_nm.h"

void	ft_fladd_back(t_file **file, t_file *new)
{
	t_file	*last;

	if (*file == NULL)
	{
		*file = new;
		return ;
	}
	last = ft_fllast(*file);
	last->next = new;
}
