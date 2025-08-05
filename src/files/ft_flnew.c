#include "commons.h"

t_file	*ft_flnew(char *filepath, int fd)
{
	t_file	*file;

	file = ft_calloc(1, sizeof(t_file));
	if (!file)
		return (NULL);
	file->filepath = filepath;
	file->fd = fd;
	file->next = NULL;
	return (file);
}
