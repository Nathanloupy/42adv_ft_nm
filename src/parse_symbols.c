#include "ft_nm.h"

/**
 * @brief Get symbol type character based on symbol info and section
 * 
 * @param bind Symbol binding
 * @param type Symbol type
 * @param shndx Section index
 * @return char Symbol type character
 */
static char	get_symbol_type_64(unsigned char bind, unsigned char type, Elf64_Section shndx)
{
	char	c;

	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
			return (shndx == SHN_UNDEF ? 'v' : 'V');
		else
			return (shndx == SHN_UNDEF ? 'w' : 'W');
	}
	if (shndx == SHN_UNDEF)
		return ('U');
	if (shndx == SHN_ABS)
		return ('A');
	if (shndx == SHN_COMMON)
		return ('C');
	if (type == STT_FUNC)
		c = 'T';
	else if (type == STT_OBJECT)
		c = 'D';
	else
		c = 'T';
	if (bind == STB_LOCAL)
		c = ft_tolower(c);
	return (c);
}

/**
 * @brief Get symbol type character based on symbol info and section
 * 
 * @param bind Symbol binding
 * @param type Symbol type
 * @param shndx Section index
 * @return char Symbol type character
 */
static char	get_symbol_type_32(unsigned char bind, unsigned char type, Elf32_Section shndx)
{
	char	c;

	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
			return (shndx == SHN_UNDEF ? 'v' : 'V');
		else
			return (shndx == SHN_UNDEF ? 'w' : 'W');
	}
	if (shndx == SHN_UNDEF)
		return ('U');
	if (shndx == SHN_ABS)
		return ('A');
	if (shndx == SHN_COMMON)
		return ('C');
	if (type == STT_FUNC)
		c = 'T';
	else if (type == STT_OBJECT)
		c = 'D';
	else
		c = 'T';
	if (bind == STB_LOCAL)
		c = ft_tolower(c);
	return (c);
}

/**
 * @brief Parse and display symbols from 64-bit ELF symbol table
 * 
 * @param file The file structure
 * @retval 1 Error
 * @retval 0 Success
 */
static int	parse_symbols_64(t_file *file)
{
	Elf64_Sym	*symtab;
	char		*strtab;
	size_t		sym_count;
	size_t		i;

	symtab = (Elf64_Sym *)file->elf_data.symtab;
	strtab = (char *)file->elf_data.strtab;
	sym_count = file->elf_data.symtab_size / file->elf_data.symtab_entsize;
	i = 0;
	while (i < sym_count)
	{
		Elf64_Sym		*sym = &symtab[i];
		char			*name = "";
		unsigned char	bind = ELF64_ST_BIND(sym->st_info);
		unsigned char	type = ELF64_ST_TYPE(sym->st_info);
		char			type_char;

		if (sym->st_name < file->elf_data.strtab_size)
			name = &strtab[sym->st_name];
		if (ft_strlen(name) == 0)
		{
			i++;
			continue;
		}
		type_char = get_symbol_type_64(bind, type, sym->st_shndx);
		if (sym->st_shndx == SHN_UNDEF)
			printf("                 %c %s\n", type_char, name);
		else
			printf("%016lx %c %s\n", sym->st_value, type_char, name);
		i++;
	}
	return (0);
}

/**
 * @brief Parse and display symbols from 32-bit ELF symbol table
 * 
 * @param file The file structure
 * @retval 1 Error
 * @retval 0 Success
 */
static int	parse_symbols_32(t_file *file)
{
	Elf32_Sym	*symtab;
	char		*strtab;
	size_t		sym_count;
	size_t		i;

	symtab = (Elf32_Sym *)file->elf_data.symtab;
	strtab = (char *)file->elf_data.strtab;
	sym_count = file->elf_data.symtab_size / file->elf_data.symtab_entsize;
	i = 0;
	while (i < sym_count)
	{
		Elf32_Sym		*sym = &symtab[i];
		char			*name = "";
		unsigned char	bind = ELF32_ST_BIND(sym->st_info);
		unsigned char	type = ELF32_ST_TYPE(sym->st_info);
		char			type_char;

		if (sym->st_name < file->elf_data.strtab_size)
			name = &strtab[sym->st_name];
		if (ft_strlen(name) == 0)
		{
			i++;
			continue;
		}
		type_char = get_symbol_type_32(bind, type, sym->st_shndx);
		if (sym->st_shndx == SHN_UNDEF)
			printf("         %c %s\n", type_char, name);
		else
			printf("%08x %c %s\n", sym->st_value, type_char, name);
		i++;
	}
	return (0);
}

/**
 * @brief Parse and display symbols from ELF symbol table
 * 
 * @param file The file structure
 * @retval 1 Error
 * @retval 0 Success
 */
int	parse_symbols(t_file *file)
{
	if (file->elf_data.is_64bit)
		return (parse_symbols_64(file));
	else
		return (parse_symbols_32(file));
}
