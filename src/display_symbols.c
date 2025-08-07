#include "ft_nm.h"
#include <stdio.h>

/**
 * @brief Display a single symbol in the standard nm format
 * 
 * @param symbol The symbol to display
 * @param file The file containing the symbol
 */
static void	display_single_symbol(t_symbol *symbol, t_file *file)
{
	if (symbol->type_char == 'U' || symbol->type_char == 'w' || symbol->type_char == 'v')
		printf("                ");
	else
	{
		if (file->elf_data.is_64bit)
			printf("%016lx", symbol->value);
		else
			printf("%08lx", symbol->value);
	}
	printf(" %c %s\n", symbol->type_char, symbol->name);
}

/**
 * @brief Display symbols from the ELF file
 * 
 * @param file The file structure containing parsed symbols
 * @retval 1 Error
 * @retval 0 Success
 */
int	display_symbols(t_file *file)
{
	size_t	i;

	if (!file || !file->elf_data.parsed_symbols)
		return (0);
	i = 0;
	while (i < file->elf_data.parsed_symbols_size)
		display_single_symbol(&file->elf_data.parsed_symbols[i++], file);
	return (0);
}