# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/28 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/12/04 09:21:24 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAIN_C		= minishell.c
BUILTINS_C	= cd.c echo.c env.c exit.c export.c pwd.c unset.c builtin_utils.c
ENVIRON_C	= envp.c envp_utils.c
EXECUTOR_C	= executor.c executor_utils.c child.c child_utils.c fds.c fds_utils.c
INPUT_C		= expander.c lexer.c lexer_utils.c lexer_utils_2.c parser.c parser_utils.c
UTILS_C		= free.c utils.c signals.c dbg_print.c

LIBFT_A		= libft/libft.a
DL_LIST_A	= dlinked_list/dlinked_list.a

NAME		= minishell
VPATH		= . built_ins environment executor input utils
SRCS		= $(MAIN_C) $(BUILTINS_C) $(ENVIRON_C) $(EXECUTOR_C) $(INPUT_C) $(UTILS_C)
OBJS_DIR	= obj
OBJS		= $(addprefix $(OBJS_DIR)/,$(SRCS:%.c=%.o))

PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
ENDC		= \033[0m

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g -O0 -Wno-multichar -I.
OFLAGS		= $(CFLAGS)
CFLAGS		+= -lreadline -L. -l:$(LIBFT_A) -l:$(DL_LIST_A)
MAKEFLAGS	+= --no-print-directory

# --------------------------------------

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) $(DL_LIST_A)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE:$(ENDC)	$@"
	@$(CC) $(OBJS) -o $@ $(CFLAGS)

$(OBJS_DIR)/%.o:	%.c | $(OBJS_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT:$(ENDC)\t$< > $@"
	@$(CC) $(OFLAGS) -c $< -o $@

$(LIBFT_A):
	@make -C "libft"

$(DL_LIST_A):
	@make -C "dlinked_list"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED! OBJECTS$(ENDC)"
	@rm -rf $(OBJS_DIR) **/*.o *.o 2>/dev/null

fclean: clean
	@$(PRINT) "$(RED), LIBRARY AND EXECUTABLE\n$(ENDC)"
	@rm -rf $(NAME) $(LIBFT_A) $(DL_LIST_A) 2>/dev/null

re:	fclean all

# --------------------------------------

print:
	@$(PRINT) "$(YELLOW)NAME:$(ENDC)\t$(NAME)"
	@$(PRINT) "$(YELLOW)SOURCES:$(ENDC)\t$(C_FILES)"
	@$(PRINT) "$(YELLOW)OBJECTS:$(ENDC)\t$(O_FILES)"
	@$(PRINT) "$(YELLOW)\nCONTENTS OF THE STACK LIBRARY:"
	@nm --print-armap $(NAME) 2>/dev/null

norm:
	@norminette -R CheckForbiddenSourceHeader **/*.c **/*.h 2>/dev/null

#debug: fclean
debug: CFLAGS += -pedantic -fsanitize=undefined -gdwarf-4 -g3 -O0
debug: OFLAGS += -g -O0
debug: all
#-fsanitize=address

release: fclean
release: CFLAGS += -Ofast -march=native -flto
release: CFLAGS += -funroll-loops -fomit-frame-pointer
release: OFLAGS += -Ofast -march=native -flto
release: OFLAGS += -funroll-loops -fomit-frame-pointer
release: all

.PHONY: all, clean, fclean, re, bonus, added, print, norm, debug, release
