NAME            = minishell

COMPILER        = cc

FLAGS           = -g3 -Wall -Wextra -Werror

LIBS            = -lreadline -lhistory

INCLUDES        = -I ./includes/

SRCS_ROOT       = ./src/

COMPILE_ROOT    = ./bin/

SRCS_FILE       = main.c \
				  test.c \
				  utils/ft_size.c \
				  utils/ft_free.c \

# Convert .c files to .o files
SRCS_COMPILE    = $(SRCS_FILE:.c=.o)

# Convert source paths to object paths, replacing src with bin
SRCS_COMPILE_PATH = $(addprefix $(COMPILE_ROOT), $(patsubst %, %, $(SRCS_COMPILE)))

MAKE_LIBFT      = $(MAKE) -C ./src/utils/libft -s

LIBFT           = ./src/utils/libft/libft.a

# Colors
GREEN = \033[0;32m
BLUE = \033[0;36m
YELLOW = \033[0;33m
PURPLE = \033[38;5;212;48;5m
NC = \033[0m

PURPLE_UNDERLINE = \033[4;38;5;212;48;5m
GREEN_UNDERLINE = \033[4;32m
YELLOW_UNDERLINE = \033[4;33m

COMPILE_MSG = "\
\n$(PURPLE_UNDERLINE)Minishell compilation:$(NC)$(PURPLE)\n\
\tLibft: $$(find ./src/utils/libft -name '*.c' | wc -l) file(s) compiled.\n\
\tMinishell: $$(expr $$(find ./src -path ./src/utils/libft -prune -o -name '*.c' | wc -l) - 1) file(s) compiled.\n\
\tHeaders: $$(find ./includes -name '*.h' | wc -l) file(s) included.\n\n\
$$(find . -name '*.a' -exec printf "\t%s created.\n" {} \;)\n\
\t./$(NAME) created.\
\n$(NC)"

CLEAN_MSG = "\
\n$(YELLOW_UNDERLINE)Cleaning information:$(NC)$(YELLOW)\n\
\t$$(find ./bin -name '*.o' | wc -l) file(s) deleted.\
$(NC)"

FCLEAN_MSG = "\
\n$(YELLOW)\
$$(find . -name '*.a' -exec printf "\t%s removed." {} \;)\n\
$$(find . -name $(NAME) -exec printf "\t%s removed." {} \;)\n\
$(NC)"

# Check if dir exist before compiling files
$(COMPILE_ROOT)%.o: $(SRCS_ROOT)%.c
	@mkdir -p $(dir $@)
	@$(COMPILER) $(FLAGS) -c $< -o $@ $(INCLUDES)

# Create program executable
$(NAME): $(SRCS_COMPILE_PATH)
	@$(MAKE_LIBFT)
	@$(COMPILER) $(FLAGS) -o $(NAME) $(SRCS_COMPILE_PATH) $(INCLUDES) $(LIBS) $(LIBFT)
	@echo $(COMPILE_MSG)

all: $(NAME)

clean:
	@echo $(CLEAN_MSG)
	@/bin/rm -f $(SRCS_COMPILE_PATH)
	@find . -name '*.o' -delete
	@$(MAKE_LIBFT) -s clean

fclean:
	@$(MAKE) -s clean
	@echo $(FCLEAN_MSG)
	@/bin/rm -f $(NAME)
	@$(MAKE_LIBFT) -s fclean

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re
