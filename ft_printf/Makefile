#/* ************************************************************************** */
#/*                                                                            */
#/*                                                        :::      ::::::::   */
#/*   Makefile                                           :+:      :+:    :+:   */
#/*                                                    +:+ +:+         +:+     */
#/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
#/*                                                +#+#+#+#+#+   +#+           */
#/*   Created: 2024/04/10 16:37:51 by csubires          #+#    #+#             */
#/*   Updated: 2024/04/22 15:48:59 by csubires         ###   ########.fr       */
#/*                                                                            */
#/* ************************************************************************** */

C_FILES	= ft_printf.c

LIBFT_FILES	= ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putnbr_base.c	\
			ft_putnbr_fd.c	\
			ft_isspace.c 	\

NAME		= libftprintf.a

HEADER		= ft_printf.h
H_FILES		= .
C_DIR		= .
O_DIR		= obj
LFT_DIR		= libft
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))
LIBFT_OF	= $(addprefix $(O_DIR)/,$(LIBFT_FILES:%.c=%.o))

PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
ENDC		= \033[0m

AR			= ar -crs
CC			= gcc
CFLAGS 		= -Wall -Werror -Wextra -g -I$(H_FILES)
MAKEFLAGS	+= --no-print-directory

# --------------------------------------

all:			$(NAME)

$(NAME):		$(O_FILES)	$(LIBFT_OF)
	@$(PRINT) "$(YELLOW)BUILDING LIBRARY:$(ENDC)\t$(NAME)"
	@$(AR) $(NAME) $(O_FILES) $(LIBFT_OF)

$(O_DIR)/%.o:	$(C_DIR)/%.c | $(O_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT:$(ENDC)\t$< > $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(O_DIR)/%.o:	$(LFT_DIR)/%.c | $(O_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT:$(ENDC)\t$< > $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(O_DIR):
	@mkdir -p $(O_DIR)

# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED!: OBJECTS$(ENDC)"
	@make -C "libft" clean
	@rm -fr $(O_DIR) *.o 2>/dev/null

fclean:	clean
	@$(PRINT) "$(RED), LIBRARY AND EXECUTABLES$(ENDC)"
	@make -C "libft" fclean
	@rm -rf $(NAME) $(LIBFT_FILE) 2>/dev/null

re:	fclean all

# --------------------------------------

print:
		@$(PRINT) "$(YELLOW)NAME LIBRARY$(ENDC):\t$(NAME)"
		@$(PRINT) "$(YELLOW)SOURCES$(ENDC):\t$(C_FILES)"
		@$(PRINT) "$(YELLOW)OBJECTS$(ENDC):\t$(O_FILES)"
		@$(PRINT) "$(YELLOW)\nCONTENTS OF THE LIBRARY FILE:"
		@nm --print-armap $(NAME) 2>/dev/null

norm:
		@norminette -R CheckForbiddenSourceHeader $(C_FILES) $(HEADER) 2>/dev/null

debug:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -pedantic -g -O0 \
	-fsanitize=address -fsanitize=undefined -fsanitize=thread" all

optimize:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -Ofast -march=native -flto -funroll-loops \
	-fomit-frame-pointer" all

.PHONY: all, clean, fclean, re, bonus, added, print, norm, debug, optimize
