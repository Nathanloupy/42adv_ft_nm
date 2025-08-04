	#include "commons.h"

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