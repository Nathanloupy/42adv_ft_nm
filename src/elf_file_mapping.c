#include "ft_nm.h"

/**
 * @brief Map an ELF file into memory, update recoverable error if any
 * 
 * @note The file is not closed, it is the responsibility of the caller to close it
 * @param file 
 * @retval 1 Unrecoverable error
 * @retval 0 Success or recoverable error
 */
int	map_elf_file(t_file *file)
{
	struct stat	st;

	if (fstat(file->fd, &st) == -1)
	{
		ft_nm_perror(file->filepath);
		file->recoverable_error |= 1;
		return (0);
	}
	file->elf_data.size = st.st_size;
	if (st.st_size == 0)
	{
		ft_nm_error_custom(file->filepath, FT_NM_FILE_FORMAT_ERROR);
		file->recoverable_error |= 1;
		return (0);
	}
	file->elf_data.data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file->fd, 0);
	if (file->elf_data.data == MAP_FAILED)
	{
		ft_nm_perror(file->filepath);
		file->recoverable_error |= 1;
		return (1);
	}
	return (0);
}
