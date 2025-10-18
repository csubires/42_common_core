# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 08:45:48 by csubires          #+#    #+#              #
#    Updated: 2024/08/17 09:13:27 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_SRV	= server.c
C_CLN	= client.c
C_BSRV	= server_bonus.c
C_BCLN	= client_bonus.c

LIBFT_FILE = libft/libft.a

PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
ENDC		= \033[0m

CC			= gcc
CFLAGS 		= -Wall -Werror -Wextra -g
MAKEFLAGS	+= --no-print-directory

# --------------------------------------

all:	server client

server:	$(C_SRV) $(LIBFT_FILE)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE:$(ENDC)	$@"
	@$(CC) $(CFLAGS) $< -o $@ -L. -l:$(LIBFT_FILE)

client:	$(C_CLN) $(LIBFT_FILE)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE:$(ENDC)	$@"
	@$(CC) $(CFLAGS) $< -o $@ -L. -l:$(LIBFT_FILE)

server_bonus:	$(C_BSRV) $(LIBFT_FILE)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE BONUS:$(ENDC)	$@"
	@$(CC) $(CFLAGS) $< -o $@ -L. -l:$(LIBFT_FILE)

client_bonus:	$(C_BCLN) $(LIBFT_FILE)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE BONUS:$(ENDC)	$@"
	@$(CC) $(CFLAGS) $< -o $@ -L. -l:$(LIBFT_FILE)

$(LIBFT_FILE):
	@make -C "libft" added

# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED!: OBJECTS$(ENDC)"
	@make -C "libft" clean

fclean:
	@make -C "libft" fclean
	@$(PRINT) "$(RED), LIBRARY AND EXECUTABLE$(ENDC)"
	@rm -rf server client server_bonus client_bonus 2>/dev/null

re:	fclean all

bonus: server_bonus client_bonus

# --------------------------------------

norm:
	@norminette -R CheckForbiddenSourceHeader *.c 2>/dev/null

debug:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -pedantic -g -O0 \
	-fsanitize=address -fsanitize=undefined -fsanitize=thread" all

optimize:	fclean
	$(MAKE) CFLAGS="$(CFLAGS) -Ofast -march=native -flto -funroll-loops \
	-fomit-frame-pointer" all

.PHONY: all, clean, fclean, re, bonus, added, print, norm, debug, optimize
