#include "ft_nm.h"

/**
 * @brief Sort symbols in ASCII order
 * 
 * @param file 
 * @retval 0 Success
 * @retval 1 Error
 */
int	sort_symbols(t_file *file)
{
	t_symbol	temp;
	size_t		i;
	size_t		j;
	char		*name_i;
	size_t		len_i;
	char		*name_j;
	size_t		len_j;
	int			multiplier = 1;

	if (file->context->flags & FT_NM_NO_SORT_FLAG)
		return (0);
	if (file->context->flags & FT_NM_REVERSE_SORT_FLAG)
		multiplier = -1;
	for (i = 0; i < file->elf_data.parsed_symbols_size; i++)
	{
		for (j = i + 1; j < file->elf_data.parsed_symbols_size; j++)
		{
			name_i = file->elf_data.parsed_symbols[i].name;
			len_i = ft_strlen(name_i);
			name_j = file->elf_data.parsed_symbols[j].name;
			len_j = ft_strlen(name_j);
			if (ft_strncmp(name_i, name_j, MAX(len_i, len_j)) * multiplier > 0)
			{
				temp = file->elf_data.parsed_symbols[i];
				file->elf_data.parsed_symbols[i] = file->elf_data.parsed_symbols[j];
				file->elf_data.parsed_symbols[j] = temp;
			}
		}
	}
	return (0);
}
