#pragma once

#include "lpyp.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define FT_NM_NAME "ft_nm"
#define FT_NM_DESC "List symbols in [FILES...] (a.out by default)."
#define FT_NM_DEFAULT_FILE "a.out"

/* ENUMS */

/* STRUCTS */
typedef struct s_elf_data {
	void	*data;
	size_t	size;
	int		is_64bit;
	int		is_big_endian;
}	t_elf_data;

typedef struct s_file
{
	char			*filepath;
	int				fd;
	int				recoverable_error;
	struct s_file	*next;
	t_elf_data		elf_data;
}	t_file;

typedef struct s_nm_context
{
	t_file			*files;
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

/* ELF FILE HANDLING */
int		map_elf_file(t_file *file);
