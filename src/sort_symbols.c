#include "ft_nm.h"

/**
 * @brief Compare two symbols
 * 
 * @param s1 The first symbol to compare
 * @param s2 The second symbol to compare
 * @return int
 */
static int	compare_symbols_fast(t_symbol *s1, t_symbol *s2)
{
	char	*str1 = s1->name;
	char	*str2 = s2->name;
	int		i = 0;

	while (str1[i] && str1[i] == str2[i])
		i++;
	if (str1[i] != str2[i])
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	if (s1->value != s2->value)
		return (s1->value < s2->value ? -1 : 1);
	return ((unsigned char)s1->type_char - (unsigned char)s2->type_char);
}

/**
 * @brief Optimized swap function
 */
static void	fast_swap(t_symbol *a, t_symbol *b)
{
	t_symbol temp = *a;
	*a = *b;
	*b = temp;
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
	size_t		i;
	size_t		j;
	size_t		n;
	int			multiplier;
	int			swapped;
	int			cmp_result;
	t_symbol	*symbols;

	if (file->context->flags & FT_NM_NO_SORT_FLAG)
		return (0);
	n = file->elf_data.parsed_symbols_size;
	if (n <= 1)
		return (0);
	symbols = file->elf_data.parsed_symbols;
	multiplier = (file->context->flags & FT_NM_REVERSE_SORT_FLAG) ? -1 : 1;
	for (i = 0; i < n - 1; i++)
	{
		swapped = 0;
		for (j = 0; j < n - i - 1; j++)
		{
			cmp_result = compare_symbols_fast(&symbols[j], &symbols[j + 1]);
			if (cmp_result * multiplier > 0)
			{
				fast_swap(&symbols[j], &symbols[j + 1]);
				swapped = 1;
			}
		}
		if (!swapped)
			break;
	}
	return (0);
}
