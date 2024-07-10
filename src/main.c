#include "../includes/minishell.h"

t_command	**create_commands_struct(int argc, char **argv, char **envp)
{
	t_command	**commands;
	char		**tmp;
	int			i;

	commands = malloc(argc * sizeof(t_command *));
	if (!commands)
		return (NULL);
	i = 0;
	while (i < argc - 1 && argv[i + 1])
	{
		tmp = ft_split(argv[i + 1], ' ');
		if (!tmp)
			return (printf("null\n"), free_t_command(commands), NULL);
		commands[i] = malloc(sizeof(t_command));
		commands[i]->command = tmp[0];
		commands[i]->options = tmp;
		commands[i]->envp = envp;
		i++;
	}
	commands[i] = NULL;
	return (commands);
}

int	main(int argc, char **argv, char **envp)
{
	t_command	**commands;

	commands = create_commands_struct(argc, argv, envp);
	free_t_command(commands);
	return (0);
}