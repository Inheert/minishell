#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;

	if (argc < 2)
		return (0);
	i = 0;
	while(argv[++i])
	{
		ft_itoa(15);
		printf("%s\n", argv[i]);
	}
	envp = (char **)envp;
	return (0);
}