# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/10/15 07:19:15 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES_C 	= dlist_add_before.c dlist_clear.c dlist_remove.c dlist_has.c	\
			dlist_last.c dlist_size.c dlist_add_after.c dlist_remove_before.c	\
			dlist_new.c dlist_free.c

NAME		= dlinked_list.a
SRCS_DIR	= .
OBJS_DIR	= ../obj
FILES_O		= $(addprefix $(OBJS_DIR)/,$(FILES_C:%.c=%.o))

PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
ENDC		= \033[0m

AR			= ar -crs
CC			= gcc
CFLAGS 		= -Wall -Werror -Wextra -I.
MAKEFLAGS	+= --no-print-directory

# --------------------------------------

all:			$(NAME)

$(NAME):		$(FILES_O) | $(OBJS_DIR)
	@$(PRINT) "\e[1A\e[K$(YELLOW)BUILDING LIBRARY:$(ENDC)\t$(NAME)\n"
	@$(AR) $(NAME) $(FILES_O)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT:$(ENDC)\t$< > $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED! OBJECTS$(ENDC)"
	@rm -fr $(OBJS_DIR) *.o 2>/dev/null

fclean: clean
	@$(PRINT) "$(RED), LIBRARY AND EXECUTABLE$(ENDC)"
	@rm -rf $(NAME) 2>/dev/null

re:	fclean all

# --------------------------------------

norm:
	@norminette -R CheckForbiddenSourceHeader *.c *.h 2>/dev/null

debug: fclean
debug: CFLAGS += -pedantic -fsanitize=undefined -gdwarf-4 -g3 -O0
debug: all

release: fclean
release: CFLAGS += -Ofast -march=native -flto
release: CFLAGS += -funroll-loops -fomit-frame-pointer
release: all

.PHONY: all, clean, fclean, re, norm, debug, release
