#include "ft_nm.h"

/**
 * @brief Get symbol type character based on symbol info and section
 * 
 * @param bind Symbol binding
 * @param type Symbol type
 * @param shndx Section index
 * @return char Symbol type character
 */
static char	get_symbol_type(unsigned char bind, unsigned char type, unsigned short shndx)
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
	size_t		sym_parsed_count;
	size_t		i;

	symtab = (Elf64_Sym *)file->elf_data.symtab;
	strtab = (char *)file->elf_data.strtab;
	if (file->elf_data.symtab_entsize != sizeof(Elf64_Sym) || file->elf_data.symtab_size == 0)
		return (error_file_format(file));
	sym_count = file->elf_data.symtab_size / file->elf_data.symtab_entsize;
	file->elf_data.parsed_symbols = ft_calloc(sym_count, sizeof(Elf64_Sym));
	if (!file->elf_data.parsed_symbols)
	{
		ft_nm_perror(NULL);
		return (1);
	}
	sym_parsed_count = 0;
	i = 0;
	while (i < sym_count)
	{
		Elf64_Sym		*sym = &symtab[i];
		char			*name = "";
		unsigned char	bind = ELF64_ST_BIND(sym->st_info);
		unsigned char	type = ELF64_ST_TYPE(sym->st_info);

		if (sym->st_name < file->elf_data.strtab_size)
			name = &strtab[sym->st_name];
		if (ft_strlen(name) == 0 || type == STT_FILE)
		{
			i++;
			continue;
		}
		file->elf_data.parsed_symbols[sym_parsed_count].name = name;
		file->elf_data.parsed_symbols[sym_parsed_count].value = sym->st_value;
		file->elf_data.parsed_symbols[sym_parsed_count].type_char = get_symbol_type(bind, type, sym->st_shndx);
		sym_parsed_count++;
		i++;
	}
	file->elf_data.parsed_symbols_size = sym_parsed_count;
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
	size_t		sym_parsed_count;
	size_t		i;

	symtab = (Elf32_Sym *)file->elf_data.symtab;
	strtab = (char *)file->elf_data.strtab;
	if (file->elf_data.symtab_entsize != sizeof(Elf32_Sym) || file->elf_data.symtab_size == 0)
		return (error_file_format(file));
	sym_count = file->elf_data.symtab_size / file->elf_data.symtab_entsize;
	file->elf_data.parsed_symbols = ft_calloc(sym_count, sizeof(Elf32_Sym));
	if (!file->elf_data.parsed_symbols)
	{
		ft_nm_perror(NULL);
		return (1);
	}
	sym_parsed_count = 0;
	i = 0;
	while (i < sym_count)
	{
		Elf32_Sym		*sym = &symtab[i];
		char			*name = "";
		unsigned char	bind = ELF32_ST_BIND(sym->st_info);
		unsigned char	type = ELF32_ST_TYPE(sym->st_info);

		if (sym->st_name < file->elf_data.strtab_size)
			name = &strtab[sym->st_name];
		if (ft_strlen(name) == 0 || type == STT_FILE)
		{
			i++;
			continue;
		}
		file->elf_data.parsed_symbols[sym_parsed_count].name = name;
		file->elf_data.parsed_symbols[sym_parsed_count].value = (unsigned long)sym->st_value;
		file->elf_data.parsed_symbols[sym_parsed_count].type_char = get_symbol_type(bind, type, sym->st_shndx);
		sym_parsed_count++;
		i++;
	}
	file->elf_data.parsed_symbols_size = sym_parsed_count;
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
	return (file->elf_data.is_64bit ? parse_symbols_64(file) : parse_symbols_32(file));
}
