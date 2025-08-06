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

	e_ident = (unsigned char *)file->elf_data.data;
	if (file->elf_data.size < EI_CLASS)
		return (error_file_format(file));
	file->elf_data.is_64bit = (e_ident[EI_CLASS] == ELFCLASS64);
	if (file->elf_data.size < (file->elf_data.is_64bit ? sizeof(Elf64_Ehdr) : sizeof(Elf32_Ehdr)))
		return (error_file_format(file));
	if (ft_memcmp(e_ident, ELFMAG, SELFMAG) != 0)
		return (error_file_format(file));
	file->elf_data.is_big_endian = (e_ident[EI_DATA] == ELFDATA2MSB);
	return (0);
}
