# Makefile for ft_nm

CC			= cc
CCFLAGS		= -Wall -Wextra -Werror

NAME		= ft_nm

INCLUDES	= -I./include/ -I./lpyp/include -I./lpyp/libft

LPYP_DIR	= lpyp
LPYP_LIB	= $(LPYP_DIR)/lpyp.a
LIBFT_LIB	= $(LPYP_DIR)/libft/libft.a

SRCS_MAIN	= src/main.c \
				src/parser.c \
				src/files_handling.c \
				src/elf_file_mapping.c \

SRCS_UTILS	= src/utils/safe_handling.c \
				src/utils/print_error.c \

SRCS_FILES	= src/files/ft_flnew.c \
				src/files/ft_fllast.c \
				src/files/ft_fladd_back.c \
				src/files/ft_flclear.c \
				src/files/ft_fldelone.c \
				src/files/ft_flsize.c \
				src/files/fldelete.c

OBJS_MAIN	= $(SRCS_MAIN:.c=.o)
OBJS_UTILS	= $(SRCS_UTILS:.c=.o)
OBJS_FILES	= $(SRCS_FILES:.c=.o)

OBJS		= $(OBJS_MAIN) $(OBJS_UTILS) $(OBJS_FILES)

%.o: %.c
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

all: $(LPYP_LIB) $(NAME)

$(LPYP_LIB):
	@make -s --no-print-directory -C $(LPYP_DIR)

$(NAME): $(OBJS) $(LPYP_LIB)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CCFLAGS) $(INCLUDES) $(OBJS) $(LPYP_LIB) $(LIBFT_LIB) -o $(NAME) -lm

clean:
	@rm -f $(OBJS)
	@make -s --no-print-directory -C $(LPYP_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -s --no-print-directory -C $(LPYP_DIR) fclean

re: fclean all

.PHONY: all clean fclean re