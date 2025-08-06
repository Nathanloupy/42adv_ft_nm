#include "ft_nm.h"

/**
 * @brief Extract symbol table and string table from a section header
 * 
 * @param file The file structure
 * @param shdr The section header for the symbol table
 * @param ehdr The ELF header
 * @param sections Array of all section headers
 * @retval 1 Error
 * @retval 0 Success
 */
static int	extract_symbol_table_64(t_file *file, Elf64_Shdr *shdr, Elf64_Ehdr *ehdr, Elf64_Shdr *sections)
{
	if (shdr->sh_offset + shdr->sh_size > file->elf_data.size)
		return (error_file_format(file));

	file->elf_data.symtab = (char *)file->elf_data.data + shdr->sh_offset;
	file->elf_data.symtab_size = shdr->sh_size;
	file->elf_data.symtab_entsize = shdr->sh_entsize;
	if (shdr->sh_link < ehdr->e_shnum)
	{
		Elf64_Shdr	*strtab_shdr = &sections[shdr->sh_link];
		if (strtab_shdr->sh_offset + strtab_shdr->sh_size > file->elf_data.size)
			return (error_file_format(file));
		file->elf_data.strtab = (char *)file->elf_data.data + strtab_shdr->sh_offset;
		file->elf_data.strtab_size = strtab_shdr->sh_size;
		return (0);
	}
	return (1);
}

/**
 * @brief Search for a specific symbol table type in ELF sections
 * 
 * @param file The file structure
 * @param ehdr The ELF header
 * @param sections Array of all section headers
 * @param section_type The type of section to search for (SHT_SYMTAB or SHT_DYNSYM)
 * @retval 1 Error or not found
 * @retval 0 Success
 */
static int	search_symbol_table_64(t_file *file, Elf64_Ehdr *ehdr, Elf64_Shdr *sections, Elf64_Word section_type)
{
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		if (sections[i].sh_type == section_type)
		{
			return (extract_symbol_table_64(file, &sections[i], ehdr, sections));
		}
	}
	return (1);
}

/**
 * @brief Find the symbol table in the ELF 64-bit file, update recoverable error if any
 * 
 * @param file 
 * @retval 1 Error
 * @retval 0 Success
 */
static int	find_symbol_table_64(t_file *file)
{
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)file->elf_data.data;
	Elf64_Shdr	*shdr = (Elf64_Shdr *)(file->elf_data.data + ehdr->e_shoff);

	if (ehdr->e_shoff == 0 || ehdr->e_shnum == 0 || ehdr->e_shentsize != sizeof(Elf64_Shdr) || ehdr->e_shoff + (ehdr->e_shnum * ehdr->e_shentsize) > file->elf_data.size)
		return (error_file_format(file));
	if (search_symbol_table_64(file, ehdr, shdr, SHT_SYMTAB) == 0)
		return (0);
	if (search_symbol_table_64(file, ehdr, shdr, SHT_DYNSYM) == 0)
		return (0);
	ft_nm_error_custom(file->filepath, "no symbols");
	file->recoverable_error = 1;
	return (1);
}

/**
 * @brief Extract symbol table and string table from a section header
 * 
 * @param file The file structure
 * @param shdr The section header for the symbol table
 * @param ehdr The ELF header
 * @param sections Array of all section headers
 * @retval 1 Error
 * @retval 0 Success
 */
static int	extract_symbol_table_32(t_file *file, Elf32_Shdr *shdr, Elf32_Ehdr *ehdr, Elf32_Shdr *sections)
{
	if (shdr->sh_offset + shdr->sh_size > file->elf_data.size)
		return (error_file_format(file));

	file->elf_data.symtab = (char *)file->elf_data.data + shdr->sh_offset;
	file->elf_data.symtab_size = shdr->sh_size;
	file->elf_data.symtab_entsize = shdr->sh_entsize;
	if (shdr->sh_link < ehdr->e_shnum)
	{
		Elf32_Shdr	*strtab_shdr = &sections[shdr->sh_link];
		if (strtab_shdr->sh_offset + strtab_shdr->sh_size > file->elf_data.size)
			return (error_file_format(file));
		file->elf_data.strtab = (char *)file->elf_data.data + strtab_shdr->sh_offset;
		file->elf_data.strtab_size = strtab_shdr->sh_size;
		return (0);
	}
	return (1);
}

/**
 * @brief Search for a specific symbol table type in ELF sections
 * 
 * @param file The file structure
 * @param ehdr The ELF header
 * @param sections Array of all section headers
 * @param section_type The type of section to search for (SHT_SYMTAB or SHT_DYNSYM)
 * @retval 1 Error or not found
 * @retval 0 Success
 */
static int	search_symbol_table_32(t_file *file, Elf32_Ehdr *ehdr, Elf32_Shdr *sections, Elf32_Word section_type)
{
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		if (sections[i].sh_type == section_type)
		{
			return (extract_symbol_table_32(file, &sections[i], ehdr, sections));
		}
	}
	return (1);
}

/**
 * @brief Find the symbol table in the ELF 32-bit file, update recoverable error if any
 * 
 * @param file 
 * @retval 1 Error
 * @retval 0 Success
 */
static int	find_symbol_table_32(t_file *file)
{
	Elf32_Ehdr	*ehdr = (Elf32_Ehdr *)file->elf_data.data;
	Elf32_Shdr	*shdr = (Elf32_Shdr *)(file->elf_data.data + ehdr->e_shoff);

	if (ehdr->e_shoff == 0 || ehdr->e_shnum == 0 || ehdr->e_shentsize != sizeof(Elf32_Shdr) || ehdr->e_shoff + (ehdr->e_shnum * ehdr->e_shentsize) > file->elf_data.size)
		return (error_file_format(file));
	if (search_symbol_table_32(file, ehdr, shdr, SHT_SYMTAB) == 0)
		return (0);
	if (search_symbol_table_32(file, ehdr, shdr, SHT_DYNSYM) == 0)
		return (0);
	ft_nm_error_custom(file->filepath, "no symbols");
	file->recoverable_error = 1;
	return (1);
}

/**
 * @brief Find the symbol table in the ELF file, update recoverable error if any
 * 
 * @param file 
 * @retval 1 Error
 * @retval 0 Success
 */
int	find_symbol_table(t_file *file)
{
	if (file->elf_data.is_64bit)
		return (find_symbol_table_64(file));
	else
		return (find_symbol_table_32(file));
}
