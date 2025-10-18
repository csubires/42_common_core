# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/08/19 08:00:07 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FILES = main.c	\
		render.c	\
		map.c	\
		parse.c	\
		utils.c

C_BONUS = main_bonus.c	\
		color_bonus.c	\
 		color_utils_bonus.c	\
		render_bonus.c	\
		render_utils_bonus.c	\
		keys_bonus.c	\
		map_bonus.c	\
		parse_bonus.c	\
		utils_bonus.c

LIBFT_FILE	= libft/libft.a
MLX_FILE	= minilibx-linux/libmlx_Linux.a

NAME		= fdf
NAME_BONUS	= fdf_bonus
C_DIR		= source
C_DIR_BONUS	= bonus
O_DIR		= obj
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))
O_BONUS		= $(addprefix $(O_DIR)/,$(C_BONUS:%.c=%.o))

PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
ENDC		= \033[0m

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g
CFLAGS 		+= -D WIN_W=1920 -D WIN_H=1080
CFLAGS 		+= -I ./include -I ./source -I ./libft -I ./minilibx-linux
CFLAGS_B	= -Wall -Werror -Wextra -g
CFLAGS_B 	+= -D WIN_W=1920 -D WIN_H=1080
CFLAGS_B	+= -I ./include -I ./source -I ./libft -I ./minilibx-linux
MLXFLAGS	= -lXext -lX11 -lm -lz
MAKEFLAGS	+= --no-print-directory
DEBUG_ARGS	= maps/42.fdf

# --------------------------------------

all:			$(NAME)

$(NAME):		$(O_FILES) $(LIBFT_FILE) $(MLX_FILE)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE:$(ENDC)	$@"
	@$(CC) $(O_FILES) -o $@ -L. -l:$(LIBFT_FILE) -l:$(MLX_FILE) $(CFLAGS) $(MLXFLAGS)

$(O_DIR)/%.o:	$(C_DIR)/%.c $(LIBFT_FILE) | $(O_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT:$(ENDC)\t$< > $@"
	@$(CC) -c $< -o $@ -L ./$(LIBFT_FILE) $(CFLAGS)

bonus:			$(NAME_BONUS)

$(NAME_BONUS):	$(O_BONUS) $(LIBFT_FILE) $(MLX_FILE)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE BONUS:$(ENDC)	$@"
	@$(CC) $(O_BONUS) -o $@ -L. -l:$(LIBFT_FILE) -l:$(MLX_FILE) $(CFLAGS_B) $(MLXFLAGS)

$(O_DIR)/%.o:	$(C_DIR_BONUS)/%.c $(LIBFT_FILE) | $(O_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)COMPILING OBJECT BONUS:$(ENDC)\t$< > $@"
	@$(CC) -c $< -o $@ -L ./$(LIBFT_FILE) $(CFLAGS_B)

$(LIBFT_FILE):
	@make -C "libft" added

$(MLX_FILE):
	@make -C "minilibx-linux" 2>/dev/null

$(O_DIR):
	@mkdir -p $(O_DIR)

# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED!: OBJECTS$(ENDC)"
	@make -C "libft" clean
	@make -C "minilibx-linux" clean
	@rm -fr $(O_DIR) *.o 2>/dev/null

fclean: clean
	@$(PRINT) "$(RED), LIBRARY AND EXECUTABLES$(ENDC)"
	@make -C "libft" fclean
	@rm -rf $(NAME) $(NAME_BONUS) 2>/dev/null

re:	fclean all

# --------------------------------------

print:
		@$(PRINT) "$(YELLOW)SOURCES:$(ENDC)\t$(C_FILES)"
		@$(PRINT) "$(YELLOW)OBJECTS:$(ENDC)\t$(O_FILES)"
		@$(PRINT) "$(YELLOW)SOURCES BONUS:$(ENDC)\t$(C_BONUS)"
		@$(PRINT) "$(YELLOW)OBJECTS BONUS:$(ENDC)\t$(O_BONUS)"
		@$(PRINT) "$(YELLOW)\nCONTENTS OF THE STACK LIBRARY:"
		@nm --print-armap $(NAME) 2>/dev/null
		@nm --print-armap $(NAME_BONUS) 2>/dev/null

norm:
	@norminette -R CheckForbiddenSourceHeader source/*.c bonus/*.c include/*.h 2>/dev/null

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
