#include "ft_nm.h"

/**
 * @brief Safe close a file descriptor function from a file struct
 * 
 * @param file 
 */
static void	safe_close(t_file *file)
{
	if (!file)
		return ;
	if (file->fd > 2)
	{
		close(file->fd);
		file->fd = -1;
	}
}

/**
 * @brief Safe munmap function from a file struct
 * 
 * @param file 
 */
static void	safe_munmap(t_file *file)
{
	if (!file || !file->elf_data.data)
		return ;
	munmap(file->elf_data.data, file->elf_data.size);
	file->elf_data.data = NULL;
	file->elf_data.size = 0;
}

/**
 * @brief Safe free parsed symbols function from a file struct
 * 
 * @param file 
 */
static void	safe_free_parsed_symbols(t_file *file)
{
	if (!file || !file->elf_data.parsed_symbols)
		return ;
	free(file->elf_data.parsed_symbols);
	file->elf_data.parsed_symbols = NULL;
	file->elf_data.parsed_symbols_size = 0;
}

/**
 * @brief Safely clean up a file struct
 * 
 * @param file 
 */
void	safe_cleanup_file(t_file *file)
{
	safe_close(file);
	safe_munmap(file);
	safe_free_parsed_symbols(file);
}

/**
* @brief Safe return function
* 
* @param context 
* @param status 
* @return int 
 */
int	safe_return(t_nm_context *context, int status)
{
	ft_flclear(&context->files, fldelete);
	return (status);
}
