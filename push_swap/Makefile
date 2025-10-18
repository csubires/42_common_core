# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/08/19 08:01:30 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FILES = ft_parse.c \
		ft_rotate.c \
		ft_calculate.c \
		ft_sort.c

C_BONUS = checker_bonus.c

LIBFT_FILE	= libft/libft.a
STACK_FILE	= stack/stack.a

NAME		= push_swap
NAME_C		= $(C_DIR)/$(NAME).c
NAME_BONUS	= checker
NAME_BC		= $(C_DIR_BONUS)/$(C_BONUS)

H_FILES		= ./source
C_DIR		= source
C_DIR_BONUS	= bonus
O_DIR		= obj
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))

PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
ENDC		= \033[0m

AR			= ar -crs
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g -gdwarf-4 -I $(H_FILES)
MAKEFLAGS	+= --no-print-directory
DEBUG_ARGS	= 667 -6493 -9456 -4915 -9222 4472 4774

# --------------------------------------

all:			$(NAME)

$(NAME):	$(NAME_C) $(O_FILES) $(LIBFT_FILE) $(STACK_FILE)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE:$(ENDC)	$@"
	@$(CC) $(CFLAGS) $(NAME_C) $(O_FILES) -L. -l:$(LIBFT_FILE) -l:$(STACK_FILE) -o $@

$(O_DIR)/%.o:	$(C_DIR)/%.c | $(O_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus:	$(NAME_BONUS)

$(NAME_BONUS):	$(NAME_BC) $(O_FILES) $(LIBFT_FILE) $(STACK_FILE)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE BONUS:$(ENDC)	$@"
	@$(CC) $(CFLAGS) $(NAME_BC) $(O_FILES) -L. -l:$(LIBFT_FILE) -l:$(STACK_FILE) -o $@

$(LIBFT_FILE):
	@make -C "libft" added

$(STACK_FILE):
	@make -C "stack"

$(O_DIR):
	@mkdir -p $(O_DIR)

# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED!: OBJECTS$(ENDC)"
	@make -C "libft" clean
	@make -C "stack" clean
	@rm -fr $(O_DIR) $(O_DIR_BONUS) *.o 2>/dev/null

fclean: clean
	@make -C "libft" fclean
	@make -C "stack" fclean
	@rm -rf $(NAME) $(NAME_BONUS) 2>/dev/null

re:	fclean all

# --------------------------------------

print:
		@$(PRINT) "$(YELLOW)NAME LIBRARY:$(ENDC)\t$(NAME)"
		@$(PRINT) "$(YELLOW)SOURCES:$(ENDC)\t$(C_FILES)"
		@$(PRINT) "$(YELLOW)OBJECTS:$(ENDC)\t$(O_FILES)"
		@$(PRINT) "$(YELLOW)\nCONTENTS OF THE STACK LIBRARY:"
		@nm --print-armap $(STACK_FILE) 2>/dev/null

norm:
	@norminette -R CheckForbiddenSourceHeader bonus/*.c source/*.c source/*.h 2>/dev/null
	@make -C "stack" norm

debug:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -pedantic -g -O0 \
	-fsanitize=address -fsanitize=undefined -fsanitize=thread" all
	gdb --args ./$(NAME) $(DEBUG_ARGS)

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	./$(NAME) $(DEBUG_ARGS)
	valgrind --tool=helgrind --track-fds=yes ./$(NAME) $(DEBUG_ARGS)

optimize:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -Ofast -march=native -flto -funroll-loops \
	-fomit-frame-pointer" all

.PHONY: all, clean, fclean, re, bonus, added, print, norm, debug, leaks, optimize
