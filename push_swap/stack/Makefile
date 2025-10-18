# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/08/17 17:06:03 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FILES = stack.c \
		movements_01.c \
		movements_02.c \
		movements_03.c \
		utils.c

NAME		= stack.a

H_FILES		= .
C_DIR		= .
O_DIR		= ../obj
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))

PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
ENDC		= \033[0m

AR			= ar -crs
CC			= gcc
CFLAGS 		= -Wall -Werror -Wextra -gdwarf-4 -g -I $(H_FILES)
MAKEFLAGS	+= --no-print-directory

# --------------------------------------

all:			$(NAME)

$(NAME):		$(O_FILES) | $(O_DIR)
	@$(PRINT) "$(YELLOW)BUILDING LIBRARY:$(ENDC)\t$(NAME)"
	@$(AR) $(NAME) $(O_FILES)

$(O_DIR)/%.o:	$(C_DIR)/%.c | $(O_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT BONUS:$(ENDC)\t$< > $@"
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
		@$(PRINT) "$(YELLOW)NAME LIBRARY:$(ENDC)\t$(NAME)"
		@$(PRINT) "$(YELLOW)SOURCES:$(ENDC)\t$(C_FILES)"
		@$(PRINT) "$(YELLOW)OBJECTS:$(ENDC)\t$(O_FILES)"
		@nm --print-armap $(NAME) 2>/dev/null

norm:
		@norminette -R CheckForbiddenSourceHeader *.c *.h 2>/dev/null

leaks:	CFLAGS += -fsanitize=address

.PHONY: all, clean, fclean, re, bonus, added, print, norm, leaks
