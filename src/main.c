#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	test[1000];

	while(1)
	{
		input = readline("Enter text: ");
		add_history(input);
		getcwd(test, 1000);
		printf("%s %s\n", getcwd(test, 1000), input);
	}
	argc = (int)argc;
	argv = (char **)argv;
	envp = (char **)envp;
	return (0);
}