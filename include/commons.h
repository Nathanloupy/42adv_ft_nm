#pragma once

#include "lpyp.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define FT_NM_NAME "ft_nm"
#define FT_NM_DESC "List symbols in [FILES...] (a.out by default)."
#define FT_NM_DEFAULT_FILE "a.out"

/* ENUMS */
typedef enum e_context_flags
{
	FT_NM_VOID = 1 << 0
}	t_context_flags;

/* STRUCTS */
typedef struct s_file
{
	char			*filepath;
	int				fd;
	int				recoverable_error;
	struct s_file	*next;
}	t_file;

typedef struct s_nm_context
{
	t_file			*files;
	t_context_flags	flags;
	int				recoverable_error;
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
void	safe_close(t_file *file);
void	ft_nm_perror(char *arg);

/* PARSER */
int		parse_arguments(int argc, char *argv[], t_nm_context *context);

/* FILES HANDLING */
int		handle_files(t_nm_context *context);
