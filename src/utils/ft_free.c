#include "../../includes/minishell.h"

void	free_str_ptr(char **ptr)
{
	size_t	i;
	size_t	size;

	if (!ptr)
		return ;
	i = 0;
	size = str_ptr_len(ptr);
	while (i < size && ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	free_t_command(t_command **commands)
{
	size_t	i;
	size_t	size;

	if (!commands || !*commands)
		return ;
	i = 0;
	size = t_command_len(commands);
	while (i < size && commands[i])
	{
		if (commands[i]->options[0] != commands[i]->command)
			free(commands[i]->command);
		free_str_ptr(commands[i]->options);
		free(commands[i]);
		i++;
	}
	free(commands);
}
