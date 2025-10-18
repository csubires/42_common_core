NAME					=	webserv

SRC						=	Cgi.cpp LocationConfig.cpp \
							main.cpp ConfigParsing.cpp Request.cpp \
							Response.cpp ResponseHeader.cpp \
							ServerConfig.cpp utils.cpp Webserv.cpp \
							ContentTypes.cpp

GREEN					=	\033[0;32m
RED						=	\033[0;31m
NO_COLOR				=	\033[0m

OBJ 					= 	$(SRC:.cpp=.o)
OBJ_DIR					=	obj
OBJ_FILES				=	$(addprefix $(OBJ_DIR)/, $(OBJ))
DEBUG_MODE				=	false

CFLAGS					=	-g -fsanitize=address -Werror -Wextra -Wall -std=c++98

ifeq ($(DEBUG_MODE), true)
    CFLAGS += -DDEBUG_MODE=true
else
    CFLAGS += -DDEBUG_MODE=false
endif

$(OBJ_DIR)/%.o			: 	src/%.cpp
							@mkdir -p $(OBJ_DIR)
							@c++ $(CFLAGS) -c $< -o $@

all						:	$(NAME)

$(NAME)					:	$(OBJ_FILES)
							@mkdir -p $(OBJ_DIR)
							@c++ $(CFLAGS) -o $(NAME) $(OBJ_FILES)
							@echo "$(GREEN)Server compiled and ready to run. Use: ./$(NAME)$(NO_COLOR)"
clean					:
							@rm -rf $(OBJ_DIR)

fclean					:	clean
							@rm -rf $(NAME)
							@echo "$(RED)Terminating potential online servers and clean.$(NO_COLOR)"
							@killall $(NAME) 2>/dev/null || true

re						:	fclean all

debug-on:
	@$(MAKE) DEBUG_MODE=true re

debug-off:
	@$(MAKE) DEBUG_MODE=false re

MAKEFLAGS	+= --no-print-directory
.PHONY					:	all clean fclean re debug-on debug-off
-include $(D_FILES)
