NAME			= minishell

COMPILER			= cc

FLAGS				= -Wall -Wextra -Werror

LIBS				= -lreadline -lhistory

INCLUDES			= -I ./includes/

SRCS_ROOT			= ./src/

COMPILE_ROOT 		= ./bin/

SRCS_FILE			= main.c \
					test.c \

SRCS_COMPILE		= $(SRCS_FILE:.c=.o)

SRCS_COMPILE_PATH 	= $(addprefix $(COMPILE_ROOT), $(SRCS_COMPILE))

MAKE_LIBFT			= $(MAKE) -C ./src/utils/libft -s

LIBFT				= ./src/utils/libft/libft.a

# Colors
GREEN = \033[0;32m
BLUE = \033[0;36m
YELLOW = \033[0;33m
NC = \033[0m

GREEN_UNDERLINE = \033[4;32m
YELLOW_UNDERLINE = \033[4;33m

$(COMPILE_ROOT)%.o	: $(SRCS_ROOT)%.c
	@cc $(FLAGS) -c $< -o $@ $(INCLUDES) $(LIBS)

$(NAME)				: $(SRCS_COMPILE_PATH)
	@echo "$(GREEN_UNDERLINE)$(COMPILE_ROOT)$(GREEN) directory created.$(NC)"
	@$(MAKE_LIBFT)
	@echo "$(GREEN_UNDERLINE)libft$(GREEN) compiled.$(NC)"
	@find $(SRCS_ROOT) -type f -name '*.o' -exec mv {} $(COMPILE_ROOT) \;
	@cc $(FLAGS) -o $(NAME) $(SRCS_COMPILE_PATH) $(INCLUDES) $(LIBS) $(LIBFT)
	@echo "$(GREEN)All files have been compiled! ($(COMPILE_ROOT))$(NC)"
	@echo "$(GREEN)Program file created: $(GREEN_UNDERLINE)$(NAME)$(NC)"



all					: $(NAME)

clean				:
	@/bin/rm -f $(COMPILE_ROOT)*.o
	@$(MAKE_LIBFT) clean
	@echo "$(YELLOW)All compiled files have been deleted!$(NC)"

fclean				:
	@/bin/rm -f $(NAME)
	@make -s clean
	@$(MAKE_LIBFT) fclean
	@echo "$(YELLOW)Program file have been removed!$(NC)"

re					:
	@make -s fclean
	@make -s all

.PHONY	: all clean fclean re
