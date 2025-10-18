
C_FILES		= 	\
	ft_arrayjoin.c	\
	ft_atoi.c	\
	ft_bzero.c	\
	ft_calloc.c	\
	ft_free_ptr.c	\
	ft_get_next_line.c	\
	ft_isdigit.c	\
	ft_isspace.c	\
	ft_itoa.c	\
	ft_memcpy.c	\
	ft_memset.c	\
	ft_printf.c	\
	ft_putchar_fd.c	\
	ft_putnbr_base.c	\
	ft_putnbr_fd.c	\
	ft_putstr_fd.c	\
	ft_strchr.c	\
	ft_strdup_from.c	\
	ft_strdup.c	\
	ft_strjoin.c	\
	ft_strlcpy.c	\
	ft_strlen.c	\
	ft_strncmp.c	\
	ft_strslen.c	\
	ft_substr.c	\
	ft_free_array.c	\
	ft_split.c	\

NAME		= libft.a
CC			= gcc
AR			= ar -crs
CFLAGS 		= -Wall -Werror -Wextra -g
O_DIR		= ../../obj
C_DIR		= .
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))

# --------------------------------------

all:		$(NAME)

$(NAME):	$(O_FILES) | $(O_DIR)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE:$(ENDC)	$@"
	@$(AR) $(NAME) $(O_FILES)

$(O_DIR)/%.o:	$(C_DIR)/%.c | $(O_DIR)
	@$(PRINT) "$(RLINE)$(BLUE)COMPILING OBJECT:$(ENDC)\t$< > $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(O_DIR):
	@mkdir -p $(O_DIR)

# --------------------------------------

clean:
	@$(PRINT) "$(CLEAR)$(RED)REMOVED! OBJECTS$(ENDC)"
	@rm -fr $(O_DIR)
fclean: clean
	@$(PRINT) "$(RED), LIBRARY, EXECUTABLE$(ENDC)"
	@rm -f $(NAME) 2>/dev/null ; true

re:	fclean all

# --------------------------------------

.PHONY: all, clean, fclean, re

PRINT		= echo
BLUE		= \e[1;34m
GREEN		= \e[1;32m
YELLOW		= \e[1;33m
RED			= \e[1;31m
MGENTA		= \e[1;35m
CYAN		= \e[1;36m
ENDC		= \e[1;0m
CLEAR		= \e[2J\e[H
RLINE		= \e[1A\e[K
MAKEFLAGS	+= --no-print-directory
