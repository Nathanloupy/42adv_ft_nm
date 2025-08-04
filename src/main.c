#include "commons.h"

static void	print_files(t_nm_context *context)
{
	t_file *file = context->files;

	while (file)
	{
		ft_putstr_fd(FT_NM_NAME, STDOUT_FILENO);
		ft_putstr_fd(": ", STDOUT_FILENO);
		ft_putstr_fd(file->filepath, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		file = file->next;
	}
}

int	main(int argc, char **argv)
{
	t_nm_context	context;

	if (parse_arguments(argc, argv, &context) != 0)
		return (safe_return(&context, 1));
	if (context.flags & FT_NM_HELP_USAGE_FLAG)
		return (safe_return(&context, 0));
	print_files(&context);
	return (safe_return(&context, 0));
}