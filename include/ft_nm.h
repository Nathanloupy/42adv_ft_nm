#pragma once

#include "lpyp.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <elf.h>

#define FT_NM_NAME "nm"
#define FT_NM_DESC "List symbols in [FILES...] (a.out by default)."
#define FT_NM_DEFAULT_FILE "a.out"

#define FT_NM_FILE_FORMAT_ERROR "file format not recognized"
#define FT_NM_NO_SYMBOLS_ERROR "no symbols"

#define FT_NM_EXTERN_ONLY_FLAG		(1 << 1)
#define FT_NM_UNDEFINED_ONLY_FLAG	(1 << 2)
#define FT_NM_REVERSE_SORT_FLAG		(1 << 3)
#define FT_NM_NO_SORT_FLAG			(1 << 4)

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* STRUCTS */
typedef struct s_symbol {
	char			*name;
	unsigned long	value;
	char			type_char;
}	t_symbol;

typedef struct s_elf_data {
	void			*data;
	size_t			size;
	int				is_64bit;
	int				is_big_endian;
	void			*sections;
	size_t			shdr_entsize;
	unsigned int	shnum;
	void			*symtab;
	void			*strtab;
	size_t			symtab_size;
	size_t			strtab_size;
	size_t			symtab_entsize;
	t_symbol		*parsed_symbols;
	size_t			parsed_symbols_size;
}	t_elf_data;

typedef struct s_file
{
	char				*filepath;
	int					fd;
	int					recoverable_error;
	struct s_file		*next;
	t_elf_data			elf_data;
	struct s_nm_context	*context;
}	t_file;

typedef struct s_nm_context
{
	t_file			*files;
	int				flags;
	int				recoverable_error;
}	t_nm_context;

/* FILES */
t_file	*ft_flnew(char *filepath, int fd, t_nm_context *context);
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

/* SYMBOL SORTING */
int		sort_symbols(t_file *file);

/* SYMBOL DISPLAY */
int		display_symbols(t_file *file);
