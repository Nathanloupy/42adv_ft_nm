#include "commons.h"

/**
 * @brief Open a file
 * 
 * @param file 
 * @retval 1 Error
 * @retval 0 Success
 */
static int	open_file(t_file *file)
{
	file->fd = open(file->filepath, O_RDONLY);
	return (file->fd == -1);
}

/**
 * @brief Handle a single file, executing the ft_nm command on it, update recoverable error if any
 * 
 * @param file 
 * @retval 1 Error
 * @retval 0 Success
 */
static int	handle_single_file(t_file *file)
{
	if (!file)
		return (0);
	if (map_elf_file(file) || file->recoverable_error)
		return (safe_cleanup_file(file), 1);
	if (validate_elf_header(file) || file->recoverable_error)
		return (safe_cleanup_file(file), 1);
	return (safe_cleanup_file(file), 0);
}

/**
 * @brief Iterate over the files, update recoverable error if any
 * 
 * @param context 
 * @retval 1 Error
 * @retval 0 Success
 */
static int	iterate_over_files(t_nm_context *context)
{
	t_file *file = context->files;

	while (file)
	{
		if (open_file(file))
		{
			ft_nm_perror(file->filepath);
			context->recoverable_error |= 1;
			file = file->next;
			continue;
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_putstr_fd(file->filepath, STDOUT_FILENO);
		ft_putstr_fd(": \n", STDOUT_FILENO);
		if (handle_single_file(file) && !file->recoverable_error)
			return (1); //TODO: maybe later print the result after the whole file is processed
		context->recoverable_error |= file->recoverable_error;
		file = file->next;
	}
	return (context->recoverable_error);
}

/**
 * @brief Handle the files
 * 
 * @param context 
 * @retval 1 Error
 * @retval 0 Success
 */
int	handle_files(t_nm_context *context)
{
	t_file *file = context->files;

	if (ft_flsize(context->files) == 1)
	{
		if (open_file(file))
		{
			ft_nm_perror(file->filepath);
			return (1);
		}
		return (handle_single_file(file));
	}
	else
		return (iterate_over_files(context));
}
