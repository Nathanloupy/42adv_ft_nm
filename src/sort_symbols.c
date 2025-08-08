#include "ft_nm.h"

/**
 * @brief Compare two strings in ASCII order
 * 
 * @param s1 The first string to compare
 * @param s2 The second string to compare
 * @return int 
 */
static int	ft_nm_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
	char		*name_j;
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
			name_j = file->elf_data.parsed_symbols[j].name;
			if (ft_nm_strcmp(name_i, name_j) * multiplier > 0)
			{
				temp = file->elf_data.parsed_symbols[i];
				file->elf_data.parsed_symbols[i] = file->elf_data.parsed_symbols[j];
				file->elf_data.parsed_symbols[j] = temp;
			}
		}
	}
	return (0);
}
