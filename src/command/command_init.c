/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 01:28:31 by Théo              #+#    #+#             */
/*   Updated: 2024/07/11 01:28:31 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		commands[i]->fd = malloc(sizeof(int[2]) * 1);
		commands[i]->envp = envp;
		i++;
	}
	commands[i] = NULL;
	return (commands);
}