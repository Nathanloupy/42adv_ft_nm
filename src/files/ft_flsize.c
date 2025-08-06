#include "ft_nm.h"

int	ft_flsize(t_file *file)
{
	if (file == NULL)
		return (0);
	return (ft_flsize(file->next) + 1);
}
