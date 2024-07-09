NAME			= minishell

COMPILER			= cc

FLAGS				= -g3 -Wall -Wextra -Werror

INCLUDES			= -I includes/

SRCS_ROOT			= ./src/

COMPILE_ROOT 		= ./bin/

SRCS_FILE			= main.c \
					test.c \

SRCS_COMPILE		= $(SRCS_FILE:.c=.o)

SRCS_COMPILE_PATH 	= $(addprefix $(COMPILE_ROOT), $(SRCS_COMPILE))

# Colors
GREEN = \033[0;32m
BLUE = \033[0;36m
YELLOW = \033[0;33m
NC = \033[0m

GREEN_UNDERLINE = \033[4;32m
YELLOW_UNDERLINE = \033[4;33m

$(COMPILE_ROOT)%.o	: $(SRCS_ROOT)%.c
	@cc $(FLAGS) -c $< -o $@ $(INCLUDES)

$(NAME)				: $(SRCS_COMPILE_PATH)
	@echo "$(GREEN_UNDERLINE)MAKE$(NC)"
	@cc -o $(NAME) $(SRCS_COMPILE_PATH)
	@echo "$(GREEN)All files have been compiled! (src folder: $(COMPILE_ROOT))$(NC)"



all					: $(NAME)

clean				:
	@/bin/rm -f $(SRCS_COMPILE_PATH)
	@echo "$(YELLOW_UNDERLINE)CLEAN$(NC)"
	@echo "$(YELLOW)All compiled files have been deleted!"

fclean				:
	@/bin/rm -f $(NAME)
	@echo "$(YELLOW_UNDERLINE)FCLEAN$(NC)"
	@echo "$(YELLOW)Executable have been removed!$(NC)\n"
	@$(MAKE) -s clean

re					:
	@echo "$(YELLOW_UNDERLINE)MAKE RE\n$(NC)"
	@$(MAKE) -s fclean
	@$(MAKE) -s

.PHONY	: all clean fclean
