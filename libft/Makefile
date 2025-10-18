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

C_FILES	= ft_isalpha.c \
			ft_isdigit.c	\
			ft_isalnum.c	\
			ft_isascii.c	\
			ft_isprint.c	\
			ft_strlen.c	\
			ft_memset.c	\
			ft_bzero.c	\
			ft_memcpy.c	\
			ft_memmove.c	\
			ft_strlcpy.c	\
			ft_strlcat.c	\
			ft_toupper.c	\
			ft_tolower.c	\
			ft_strchr.c	\
			ft_strrchr.c	\
			ft_strncmp.c	\
			ft_memchr.c	\
			ft_memcmp.c	\
			ft_strnstr.c	\
			ft_atoi.c	\
			ft_calloc.c	\
			ft_strdup.c	\
			ft_substr.c	\
			ft_strjoin.c	\
			ft_strtrim.c	\
			ft_split.c	\
			ft_itoa.c	\
			ft_strmapi.c	\
			ft_striteri.c	\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c

C_UTILS = ft_free_ptr.c	\
			ft_isspace.c \
			ft_nbrlen.c	\
			ft_isinset.c	\
			ft_putnbr_base.c	\
			ft_striter.c	\
			ft_atoi_base.c	\
			ft_atoi_err.c	\
			ft_minimum.c	\
			ft_maximum.c	\
			ft_abs.c	\
			ft_free_split.c

C_BONUS	= ft_lstnew.c	\
			ft_lstadd_front.c	\
			ft_lstsize.c	\
			ft_lstlast.c	\
			ft_lstadd_back.c	\
			ft_lstdelone.c	\
			ft_lstclear.c	\
			ft_lstiter.c	\
			ft_lstmap.c

C_ADDED = ft_printf.c	\
			ft_get_next_line.c

NAME		= libft.a
HEADER		= libft.h
H_FILES		= .
C_DIR		= .
C_DIR_BONUS	= .
O_DIR		= obj
O_DIR_BONUS	= obj_bonus
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))
O_UTILS		= $(addprefix $(O_DIR)/,$(C_UTILS:%.c=%.o))
O_ADDED		= $(addprefix $(O_DIR)/,$(C_ADDED:%.c=%.o))
O_BONUS		= $(addprefix $(O_DIR_BONUS)/,$(C_BONUS:%.c=%.o))

PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
ENDC		= \033[0m

AR			= ar -crs
CC			= gcc
CFLAGS 		= -Wall -Werror -Wextra -g -fPIE -I$(H_FILES)
# --------------------------------------

all:			$(NAME)

$(NAME):		$(O_FILES) $(O_UTILS) | $(O_DIR)
	@$(PRINT) "$(YELLOW)BUILDING LIBRARY:$(ENDC)\t$(NAME)"
	@$(AR) $(NAME) $(O_FILES) $(O_UTILS)

$(O_DIR)/%.o:	$(C_DIR)/%.c | $(O_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT:$(ENDC)\t$< > $@"
	@$(CC) $(CFLAGS) -c $< -o $@

added:			$(NAME) $(O_ADDED) | $(O_DIR)
	@$(PRINT) "$(YELLOW)BUILDING LIBRARY WITH \"ADDED FUNCTIONS\":$(ENDC)\t$(NAME)"
	@$(AR) $(NAME) $(O_ADDED)

bonus:			$(NAME) $(O_BONUS) | $(O_DIR_BONUS)
	@$(PRINT) "$(YELLOW)BUILDING LIBRARY WITH \"BONUS\":$(ENDC)\t$(NAME)"
	@$(AR) $(NAME) $(O_BONUS)

$(O_DIR_BONUS)/%.o:	$(C_DIR_BONUS)/%.c | $(O_DIR_BONUS)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT BONUS:$(ENDC)\t$< > $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(O_DIR):
	@mkdir -p $(O_DIR)

$(O_DIR_BONUS):
	@mkdir -p $(O_DIR_BONUS)

# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED!: OBJECTS$(ENDC)"
	@rm -fr $(O_DIR) $(O_DIR_BONUS) *.o 2>/dev/null

fclean: clean
	@$(PRINT) "\r$(RED), LIBRARY AND EXECUTABLE$(ENDC)"
	@rm -f $(NAME) 2>/dev/null

re:	fclean all

# --------------------------------------

print:
		@$(PRINT) "$(YELLOW)NAME LIBRARY:$(ENDC)\t$(NAME)"
		@$(PRINT) "$(YELLOW)SOURCES:$(ENDC)\t$(C_FILES)"
		@$(PRINT) "$(YELLOW)OBJECTS:$(ENDC)\t$(O_FILES)"
		@$(PRINT) "$(YELLOW)SOURCES UTILS:$(ENDC)\t$(C_UTILS)"
		@$(PRINT) "$(YELLOW)OBJECTS UTILS:$(ENDC)\t$(O_UTILS)"
		@$(PRINT) "$(YELLOW)SOURCES ADDED:$(ENDC)\t$(C_ADDED)"
		@$(PRINT) "$(YELLOW)OBJECTS ADDED:$(ENDC)\t$(O_ADDED)"
		@$(PRINT) "$(YELLOW)SOURCES BONUS:$(ENDC)\t$(C_BONUS)"
		@$(PRINT) "$(YELLOW)OBJECTS BONUS:$(ENDC)\t$(O_BONUS)"
		@$(PRINT) "$(YELLOW)\nCONTENTS OF THE LIBRARY FILE:"
		@nm --print-armap $(NAME) 2>/dev/null

norm:
		@norminette -R CheckForbiddenSourceHeader $(C_FILES) $(C_BONUS) $(C_UTILS) $(C_ADDED) $(HEADER) 2>/dev/null

debug:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -pedantic -g -O0 \
	-fsanitize=address -fsanitize=undefined -fsanitize=thread" all

optimize:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -Ofast -march=native -flto -funroll-loops \
	-fomit-frame-pointer" all

.PHONY: all, clean, fclean, re, bonus, added, print, norm, debug, optimize
