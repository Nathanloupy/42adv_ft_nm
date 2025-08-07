#pragma once

#include "lpyp.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>

#define FT_NM_NAME "ft_nm"
#define FT_NM_DESC "List symbols in [FILES...] (a.out by default)."
#define FT_NM_DEFAULT_FILE "a.out"

#define FT_NM_FILE_FORMAT_ERROR "file format not recognized"

/* ENUMS */

/* STRUCTS */
typedef struct s_elf_data {
	void	*data;
	size_t	size;
	int		is_64bit;
	int		is_big_endian;
	void	*symtab;
	void	*strtab;
	size_t	symtab_size;
	size_t	strtab_size;
	size_t	symtab_entsize;
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
void	safe_cleanup_file(t_file *file);
int		safe_return(t_nm_context *context, int status);
void	ft_nm_perror(char *arg);
void	ft_nm_error_custom(char *arg, char *error_message);
int		error_file_format(t_file *file);

/* PARSER */
int		parse_arguments(int argc, char *argv[], t_nm_context *context);

/* FILES HANDLING */
int		handle_files(t_nm_context *context);

/* ELF FILE HANDLING */
int		map_elf_file(t_file *file);

/* ELF HEADER VALIDATION */
int		validate_elf_header(t_file *file);

/* ELF SYMBOL TABLE */
int		find_symbol_table(t_file *file);

/* SYMBOL PARSING */
int		parse_symbols(t_file *file);
