NAME			= minishell

COMPILER			= cc

FLAGS				= -Wall -Wextra -Werror

INCLUDES			= -I includes/

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
	@cc $(FLAGS) -c $< -o $@ $(INCLUDES)

$(NAME)				: $(SRCS_COMPILE_PATH)
	@mkdir -p $(COMPILE_ROOT)
	@$(MAKE_LIBFT)
	@find $(SRCS_ROOT) -type f -name '*.o' -exec mv {} $(COMPILE_ROOT) \;
	@cc $(FLAGS) -o $(NAME) $(SRCS_COMPILE_PATH) $(INCLUDES) $(LIBFT)
	@echo "$(GREEN)All files have been compiled! ($(COMPILE_ROOT))$(NC)"
	@echo "$(GREEN)Program file created: $(NAME)$(NC)"



all					: $(NAME)

clean				:
	@/bin/rm -f $(COMPILE_ROOT)*.o
	@$(MAKE_LIBFT) clean
	@echo "$(YELLOW)All compiled files have been deleted!$(NC)"

fclean				:
	@/bin/rm -f $(NAME)
	@make -s clean
	@$(MAKE_LIBFT) fclean
	@echo "$(YELLOW)Programe file have been removed!$(NC)"

re					:
	@make -s fclean
	@make -s all

.PHONY	: all clean fclean re
