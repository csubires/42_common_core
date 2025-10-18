C_FILES		= AForm.cpp Bureaucrat.cpp PresidentialPardonForm.cpp RobotomyRequestForm.cpp ShrubberyCreationForm.cpp main.cpp Intern.cpp

NAME		= intern
H_FILES		= .
C_DIR		= .
O_DIR		= obj
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.cpp=%.o))
D_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.cpp=%.d))

CC			= c++
CFLAGS		= -std=c++98 -Wall -Wextra -Werror -g
DEPFLAGS	= -MMD -MP
CFLAGS		+= $(DEPFLAGS) -I $(H_FILES)

# --------------------------------------

all:			$(NAME)

$(NAME):		$(O_FILES)
	@$(PRINT) "$(GREEN)COMPILING EXECUTABLE:$(ENDC)	$@"
	@$(CC) $(CFLAGS) $^ -o $@

$(O_DIR)/%.o:	$(C_DIR)/%.cpp | $(O_DIR)
	@$(PRINT) "$(RLINE)$(BLUE)COMPILING OBJECT:$(ENDC)\t$< > $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(O_DIR):
	@mkdir -p $(O_DIR)

# --------------------------------------

clean:
	@$(PRINT) "$(CLEAR)$(RED)REMOVED! OBJECTS$(ENDC)"
	@rm -rf $(O_DIR) *.o *.d 2>/dev/null

fclean: clean
	@$(PRINT) "$(RED), LIBRARY AND EXECUTABLE\n$(ENDC)"
	@rm -rf $(NAME) 2>/dev/null

re:	fclean all

# --------------------------------------

.PHONY: all, clean, fclean, re
-include $(D_FILES)

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
