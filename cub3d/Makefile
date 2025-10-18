
C_FILES = main.c map.c map_utils.c parse.c keys.c render.c render_utils.c utils.c

LIBFT_FILE	= lib/libft/libft.a
MLX42_FILE	= lib/MLX42/build/libmlx42.a
GLFW_FILE	= /lib/MLX42/build/_deps/glfw-build/src/libglfw3.a
LIB_PKG		= lib/MLX42.zip

NAME		= cub3D
CC			= gcc
O_DIR		= obj
C_DIR		= source
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))

CFLAGS		= -Wall -Werror -Wextra -g
LIBS		= -L. -l:$(LIBFT_FILE) -l:$(MLX42_FILE) -l:$(GLFW_FILE)
MLXFLAGS	= -lX11 -ldl -pthread -lm -ffast-math

# --------------------------------------

all: $(NAME)

$(NAME):	$(O_FILES) $(LIBFT_FILE) $(MLX42_FILE)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE:$(ENDC)	$@"
	@$(CC) $(O_FILES) -o $@ $(LIBS) $(CFLAGS) $(MLXFLAGS)

$(O_DIR)/%.o:	$(C_DIR)/%.c $(LIBFT_FILE) $(MLX42_FILE) | $(O_DIR)
	@$(PRINT) "$(RLINE)$(BLUE)COMPILING OBJECT:$(ENDC)\t$< > $@"
	@$(CC) -c $< -o $@ $(LIBS) $(CFLAGS) $(MLXFLAGS)

$(LIBFT_FILE):
	@make -C "lib/libft"

$(MLX42_FILE):
	@unzip $(LIB_PKG) -d lib 2>/dev/null ; true
	@cmake -S "lib/MLX42" -B "lib/MLX42/build" 2>/dev/null ; true
	@cmake --build "lib/MLX42/build" 2>/dev/null ; true

$(O_DIR):
	@mkdir -p $(O_DIR)

# --------------------------------------

clean:
	@$(PRINT) "$(CLEAR)$(RED)REMOVED! OBJECTS$(ENDC)"
	@make -C "lib/libft" clean
	@rm -fr $(O_DIR) *.o 2>/dev/null ; true
	@rm -fr lib/MLX42 2>/dev/null ; true

fclean: clean
	@$(PRINT) "$(RED), LIBRARY, EXECUTABLE$(ENDC)"
	@make -C "lib/libft" fclean
	@rm -fr $(NAME) 2>/dev/null ; true

re:	fclean all

# --------------------------------------

.PHONY: all, clean, fclean, re

PRINT		= echo
BLUE		= \e[1;34m
GREEN		= \e[1;32m
YELLOW		= \e[1;33m
RED			= \e[1;31m
MGENTA		= \e[1;35m
CYAN		= \e[1;36m
ENDC		= \e[1;0m
CLEAR		= \e[2J\e[H
RLINE		= \e[1A\e[K
MAKEFLAGS	+= --no-print-directory
