# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/09/10 17:44:03 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FILES = main_bonus.c	\
		actions_bonus.c	\
		control_bonus.c	\
		process_bonus.c	\
		utils_bonus.c

NAME		= philo
H_FILES		= include
C_DIR		= source
O_DIR		= obj
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))

PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
ENDC		= \033[0m

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I $(H_FILES)
MAKEFLAGS	+= --no-print-directory
DEBUG_ARGS	= 1 800 200 200

# --------------------------------------

all:	$(NAME)

$(NAME):	$(O_FILES)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE BONUS:$(ENDC)	$@"
	@$(CC) $(CFLAGS) $(O_FILES) -o $@

$(O_DIR)/%.o:	$(C_DIR)/%.c | $(O_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT BONUS:$(ENDC)\t$<	->	$@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(O_DIR):
	@mkdir -p $(O_DIR)

# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED! OBJECTS$(ENDC)"
	@rm -fr $(O_DIR) *.o 2>/dev/null

fclean: clean
	@$(PRINT) "$(RED), LIBRARY AND EXECUTABLE$(ENDC)"
	@rm -rf $(NAME) 2>/dev/null

re:	fclean all

# --------------------------------------

print:
		@$(PRINT) "$(YELLOW)NAME:$(ENDC)\t$(NAME)"
		@$(PRINT) "$(YELLOW)SOURCES:$(ENDC)\t$(C_FILES)"
		@$(PRINT) "$(YELLOW)OBJECTS:$(ENDC)\t$(O_FILES)"
		@$(PRINT) "$(YELLOW)\nCONTENTS OF THE STACK LIBRARY:"
		@nm --print-armap $(NAME) 2>/dev/null

norm:
	@norminette -R CheckForbiddenSourceHeader source/*.c source/*.h 2>/dev/null

debug:		fclean
	$(MAKE) CFLAGS="$(CFLAGS) -pedantic -g -O0 \
	-fsanitize=undefined -fsanitize=thread" all
	gdb --args ./$(NAME) $(DEBUG_ARGS)

valg:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -g -O0 -lpthread" all
	@$(PRINT) "\n$(YELLOW) [▲] VALGRIND --LEAK-CHECK=FULL\n$(ENDC)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	./$(NAME) $(DEBUG_ARGS)
	@$(PRINT) "\n$(YELLOW) [▲] VALGRIND --TOOL=HELGRIND\n$(ENDC)"
	valgrind --tool=helgrind --track-fds=yes --history-level=approx ./$(NAME) $(DEBUG_ARGS)
	@$(PRINT) "\n$(YELLOW) [▲] VALGRIND --TOOL=DRD\n$(ENDC)"
	valgrind --tool=drd ./$(NAME) $(DEBUG_ARGS)
	@$(PRINT) "\n$(YELLOW) [▲] VALGRIND --TOOL=MEMCHECK\n$(ENDC)"
	valgrind --tool=memcheck --leak-check=full ./$(NAME) $(DEBUG_ARGS)

optimize:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -Ofast -march=native -flto -funroll-loops \
	-fomit-frame-pointer" all

.PHONY: all, clean, fclean, re, bonus, added, print, norm, debug, valg, optimize
