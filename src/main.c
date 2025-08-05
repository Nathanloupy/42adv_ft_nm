#include "commons.h"

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @retval 1 Error
 * @retval 0 Success
 */
int	main(int argc, char **argv)
{
	t_nm_context	context;

	if (parse_arguments(argc, argv, &context))
		return (safe_return(&context, 1));
	if (handle_files(&context))
		return (safe_return(&context, 1));
	return (safe_return(&context, context.recoverable_error));
}