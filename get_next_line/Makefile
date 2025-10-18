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

C_FILES	= get_next_line.c
C_BONUS = get_next_line_bonus.c

LIBFT_FILE	= libft/libft.a

NAME		= obj/main.out
NAME_C		= tests/main.c
HEADER		= get_next_line.h
HEADER_B	= get_next_line_bonus.h
H_FILES		= .
C_DIR		= .
O_DIR		= obj
O_DIR_BONUS = obj
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))
O_BONUS		= $(addprefix $(O_DIR)/,$(C_BONUS:%.c=%.o))

PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
ENDC		= \033[0m

BUFFER_SIZE	= 1000
AR			= ar -crs
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g
CFLAGS 		+= -D BUFFER_SIZE=$(BUFFER_SIZE) -I$(H_FILES)
MAKEFLAGS	+= --no-print-directory

# --------------------------------------

all:	$(NAME)

$(NAME):	$(NAME_C) $(O_FILES) $(LIBFT_FILE)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE:$(ENDC)	$@"
	@$(CC) $(CFLAGS) $(NAME_C) $(O_FILES) -L. -l:$(LIBFT_FILE) -o $@

$(O_DIR)/%.o:	$(C_DIR)/%.c | $(O_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT:$(ENDC)\t$< > $@"
	@$(CC) $(CFLAGS) -c $< -o $@

bonus:	$(NAME_C) $(O_BONUS) $(LIBFT_FILE)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE BONUS:$(ENDC)	$@"
	@$(CC) $(CFLAGS) $(NAME_C) $(O_BONUS) -L. -l:$(LIBFT_FILE) -o $(NAME)

$(O_DIR)/%.o:	$(C_DIR)/%.c | $(O_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT BONUS:$(ENDC)\t$< > $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_FILE):
	@make -C "libft"

$(O_DIR):
	@mkdir -p $(O_DIR)

# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED!: OBJECTS$(ENDC)"
	@make -C "libft" clean
	@rm -fr -v $(O_DIR) $(O_DIR_BONUS) *.o 2>/dev/null

fclean:	clean
	@$(PRINT) "$(RED), LIBRARY AND EXECUTABLES$(ENDC)"
	@make -C "libft" fclean
	@rm -rf -v $(NAME) $(LIBFT_FILE) 2>/dev/null

re:	fclean all

# --------------------------------------

print:
		@$(PRINT) "$(YELLOW)NAME LIBRARY$(ENDC):\t$(NAME)\n"
		@$(PRINT) "$(YELLOW)SOURCES$(ENDC):\t$(C_FILES)\n"
		@$(PRINT) "$(YELLOW)OBJECTS$(ENDC):\t$(O_FILES)\n\n"
		@$(PRINT) "$(YELLOW)SOURCES BONUS$(ENDC):\t$(C_BONUS)\n"
		@$(PRINT) "$(YELLOW)OBJECTS BONUS$(ENDC):\t$(O_BONUS)\n"
		@$(PRINT) "$(YELLOW)\nCONTENTS OF THE LIBRARY FILE:"
		@nm --print-armap $(NAME) 2>/dev/null

norm:
		@norminette -R CheckForbiddenSourceHeader $(C_FILES) $(C_BONUS) $(HEADER) $(HEADER_B) 2>/dev/null

debug:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -pedantic -g -O0 \
	-fsanitize=address -fsanitize=undefined -fsanitize=thread" all

optimize:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -Ofast -march=native -flto -funroll-loops \
	-fomit-frame-pointer" all

.PHONY: all, clean, fclean, re, bonus, added, print, norm, debug, optimize
