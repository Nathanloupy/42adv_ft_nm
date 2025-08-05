#include "commons.h"

int	map_elf_file(t_file *file)
{
	struct stat st;
	
	if (fstat(file->fd, &st) == -1)
	{
		ft_nm_perror(file->filepath);
		file->recoverable_error |= 1;
		return (0);
	}
	file->elf_data.size = st.st_size;
	file->elf_data.data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file->fd, 0);
	if (file->elf_data.data == MAP_FAILED)
	{
		ft_nm_perror(file->filepath);
		file->recoverable_error |= 1;
		return (0);
	}
	return (0);
}
