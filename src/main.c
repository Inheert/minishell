#include "../includes/minishell.h"

t_command	**create_commands_struct(int argc, char **argv, char **envp)
{
	t_command	**commands;
	char		**tmp;
	int			i;

	commands = malloc(argc * sizeof(t_command *));
	if (!commands)
		return (NULL);
	i = 1;
	while (i <= argc && argv[i])
	{
		tmp = ft_split(argv[i], ' ');
		if (!tmp)
			return (free(commands), NULL);
		commands[i] = malloc(sizeof(t_command));
		commands[i]->command = tmp[0];
		commands[i]->options = tmp;
		commands[i]->envp = envp;
		printf("%s\n", argv[i]);
		i++;
	}
	return (commands);
}

int	main(int argc, char **argv, char **envp)
{
	create_commands_struct(argc, argv, envp);
	argc = (int)argc;
	argv = (char **)argv;
	envp = (char **)envp;
	return (0);
}