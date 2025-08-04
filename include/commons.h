#pragma once

#include "lpyp.h"
#include <errno.h>
#include <string.h>

#define FT_NM_NAME "ft_nm"
#define FT_NM_DESC "List symbols in [FILES...] (a.out by default)."
#define FT_NM_DEFAULT_FILE "a.out"

/* ENUMS */
typedef enum e_context_flags
{
	FT_NM_HELP_USAGE_FLAG = 1 << 0
}	t_context_flags;

/* STRUCTS */
typedef struct s_file
{
	char			*filepath;
	int				fd;
	struct s_file	*next;
}	t_file;

typedef struct s_nm_context
{
	t_file			*files;
	t_context_flags	flags;
}	t_nm_context;

/* FILES */
t_file	*ft_flnew(char *filepath, int fd);
t_file	*ft_fllast(t_file *file);
void	ft_fladd_back(t_file **file, t_file *new);
void	ft_flclear(t_file **file, void (*del)(void*));
void	ft_fldelone(t_file *file, void (*del)(void*));
int		ft_flsize(t_file *file);
void	fldelete(void *data);

/* UTILS */
int		safe_return(t_nm_context *context, int status);
void	ft_nm_perror(char *function_name);

/* PARSER */
int		parse_arguments(int argc, char *argv[], t_nm_context *context);
