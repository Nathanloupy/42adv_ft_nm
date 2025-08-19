#include "ft_nm.h"
#include "lpyp.h"
#include <stdlib.h>

/**
 * @brief ft_nm options definition
 */
static t_lpyp_options	ft_nm_options[] = {
{'p', "no-sort", 'p', LPYP_NO_ARG, "do not sort the symbols", NULL},
{'r', "reverse", 'r', LPYP_NO_ARG, "reverse the sense of the sort", NULL},
{'u', "undefined-only", 'u', LPYP_NO_ARG, "display only undefined symbols", NULL},
{'g', "extern-only", 'g', LPYP_NO_ARG, "display only external symbols", NULL},
{'h', "help", 'h', LPYP_NO_ARG, "give this help list", NULL},
{0, "usage", 'U', LPYP_NO_ARG, "give a short usage message", NULL},
{0, NULL, LPYP_KEY_ARG, 0, NULL, "FILES..."},
{0, NULL, 0, 0, NULL, NULL} /* Sentinel */
};

/**
 * @brief ft_nm parser callback function
 *
 * @param key
 * @param data
 * @param argument
 * @retval 0 Success
 * @retval 1 Error
 */
static int	ft_nm_parser(unsigned int key, void *data, char *argument)
{
	t_nm_context	*context = (t_nm_context *)data;

	switch (key)
	{
		case 'h':
		{
			lpyp_help(ft_nm_options, FT_NM_NAME, FT_NM_DESC);
			exit(safe_return(context, 0));
		}
		case 'U':
		{
			lpyp_usage(ft_nm_options, FT_NM_NAME);
			exit(safe_return(context, 0));
		}
		case 'g':
		{
			context->flags |= FT_NM_EXTERN_ONLY_FLAG;
			break ;
		}
		case 'u':
		{
			context->flags |= FT_NM_UNDEFINED_ONLY_FLAG;
			break ;
		}
		case 'r':
		{
			context->flags |= FT_NM_REVERSE_SORT_FLAG;
			break ;
		}
		case 'p':
		{
			context->flags |= FT_NM_NO_SORT_FLAG;
			break ;
		}
		case LPYP_KEY_ARG:
		{
			t_file	*file = ft_flnew(argument, -1, context);
			if (!file)
			{
				ft_nm_perror(NULL);
				return (safe_return(context, 1));
			}
			ft_fladd_back(&context->files, file);
			break ;
		}
		case LPYP_KEY_END:
		{
			if (ft_flsize(context->files) == 0)
				return (ft_nm_parser(LPYP_KEY_ARG, data, FT_NM_DEFAULT_FILE));
			break ;
		}
		case LPYP_KEY_UNKNOWN:
		{
			lpyp_help(ft_nm_options, FT_NM_NAME, FT_NM_DESC);
			return (safe_return(context, 1));
		}
	}
	return (0);
}

/**
 * @brief Parse command line arguments using lpyp
 * 
 * @param argc 
 * @param argv 
 * @param context 
 * @retval 0 Success
 * @retval 1 Error
 */
int	parse_arguments(int argc, char *argv[], t_nm_context *context)
{
	ft_memset(context, 0, sizeof(t_nm_context));
	return (lpyp_parse(context, argc, argv, ft_nm_options, ft_nm_parser));
}
