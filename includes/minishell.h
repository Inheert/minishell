#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/utils/libft/libft.h"

typedef struct s_command
{
	char	**envp;
	char	*command;
	char	*options;
	int		fd[2];
}	t_command;

void	test(void);

#endif