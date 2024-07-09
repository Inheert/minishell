#include <stdio.h>
#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	argc = (int)argc;
	argv = (char **)argv;
	envp = (char **)envp;
	printf("Argc: %d\n", argc);
	test();
	return (0);
}