# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/12/04 09:23:32 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES_C		= ft_atoi.c ft_isprint.c ft_isspace.c ft_itoa.c ft_split.c \
			ft_strdup.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_substr.c ft_strcmp.c \
			ft_strchr.c ft_strconcat.c ft_fdprint.c ft_calloc.c ft_strltrim.c ft_isallalpha.c

NAME		= libft.a
SRCS_DIR	= .
OBJS_DIR	= ../obj
O_FILES		= $(addprefix $(OBJS_DIR)/,$(FILES_C:%.c=%.o))

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

$(NAME):		$(O_FILES) | $(OBJS_DIR)
	@$(PRINT) "\e[1A\e[K$(YELLOW)BUILDING LIBRARY:$(ENDC)\t$(NAME)\n"
	@$(AR) $(NAME) $(O_FILES)

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
