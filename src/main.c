#include "commons.h"

int	main(int argc, char **argv)
{
	t_nm_context	context;

	if (parse_arguments(argc, argv, &context))
		return (safe_return(&context, 1));
	if (handle_files(&context))
		return (safe_return(&context, 1));
	return (safe_return(&context, context.recoverable_error));
}