#include "ft_nm.h"

/**
 * @brief symbol The symbol to check
 * @retval 1 Undefined
 * @retval 0 Not undefined
 */
static int	is_undefined_symbol(t_symbol *symbol)
{
	return (symbol->type_char == 'U' || symbol->type_char == 'w' || symbol->type_char == 'v');
}

/**
 * @brief Check if a symbol is an external symbol
 * 
 * @param symbol The symbol to check
 * @retval 1 External
 * @retval 0 Not external
 */
static int	is_external_symbol(t_symbol *symbol)
{
	return (('A' <= symbol->type_char && symbol->type_char <= 'Z') || is_undefined_symbol(symbol));
}

/**
 * @brief Print a hexadecimal value in lower case
 * 
 * @param value The value to print
 * @param is8byte Whether the value is 8 or 16 bytes
 */
static void	print_hex_lower(unsigned long value, char is16byte)
{
	char		buffer16[16];
	char		buffer8[8];
	const char	*base = "0123456789abcdef";

	if (is16byte)
	{
		for (int i = 15; i >= 0; --i)
		{
			buffer16[i] = base[value & 0xF];
			value >>= 4;
		}
		write(1, buffer16, 16);
	}
	else
	{
		for (int i = 7; i >= 0; --i)
		{
			buffer8[i] = base[value & 0xF];
			value >>= 4;
		}
		write(1, buffer8, 8);
	}
}

/**
 * @brief Display a single symbol in the standard nm format
 * 
 * @param symbol The symbol to display
 * @param file The file containing the symbol
 */
static void	display_single_symbol(t_symbol *symbol, t_file *file)
{
	if (!is_undefined_symbol(symbol) && (file->context->flags & FT_NM_UNDEFINED_ONLY_FLAG))
		return ;
	if (!is_external_symbol(symbol) && (file->context->flags & FT_NM_EXTERN_ONLY_FLAG))
		return ;
	if (is_undefined_symbol(symbol))
		ft_putstr_fd("                ", 1);
	else
		print_hex_lower(symbol->value, file->elf_data.is_64bit);
	ft_putstr_fd(" ", 1);
	ft_putchar_fd(symbol->type_char, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(symbol->name, 1);
	ft_putstr_fd("\n", 1);
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
