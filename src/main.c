#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	while(1)
	{
		input = readline("Enter text: ");
		add_history(input);
		printf("%s\n", input);
	}
	argc = (int)argc;
	argv = (char **)argv;
	envp = (char **)envp;
	return (0);
}