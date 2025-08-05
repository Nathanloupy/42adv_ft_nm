#include "commons.h"

t_file	*ft_fllast(t_file *file)
{
	if (!file)
		return (NULL);
	if (file->next == NULL)
		return (file);
	return (ft_fllast(file->next));
}
