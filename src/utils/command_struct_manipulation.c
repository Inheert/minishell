#include "../../includes/minishell.h"

ssize_t	str_ptr_len(char **ptr)
{
	ssize_t	size;

	if (!ptr || !*ptr)
		return (0);
	size = 0;
	while (ptr[size])
		size++;
	return (size);
}

ssize_t	t_command_len(t_command **commands)
{
	ssize_t	size;

	if (!commands || !*commands)
		return (0);
	size = 0;
	while (commands[size])
		size++;
	return (size);
}

void	free_str_ptr(char **ptr)
{
	ssize_t	size;

	if (!ptr)
		return ;
	size = str_ptr_len(ptr);
	while (ptr[size])
		free(ptr[size++]);
	free(ptr);
}
