#include "ft_nm.h"

/**
 * @brief Check if the ELF header is valid, update recoverable error if any
 * 
 * @param file 
 * @retval 1 Error
 * @retval 0 Success
 */
int	validate_elf_header(t_file *file)
{
	unsigned char *e_ident;
	
	if (file->elf_data.size < sizeof(Elf64_Ehdr))
	{
		ft_nm_error_custom(file->filepath, FT_NM_FILE_FORMAT_ERROR);
		file->recoverable_error = 1;
		return (1);
	}
	e_ident = (unsigned char *)file->elf_data.data;
	if (ft_memcmp(e_ident, ELFMAG, SELFMAG) != 0)
	{
		ft_nm_error_custom(file->filepath, FT_NM_FILE_FORMAT_ERROR);
		file->recoverable_error = 1;
		return (1);
	}
	file->elf_data.is_64bit = (e_ident[EI_CLASS] == ELFCLASS64);
	file->elf_data.is_big_endian = (e_ident[EI_DATA] == ELFDATA2MSB);
	return (0);
}
