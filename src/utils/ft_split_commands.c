/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 01:36:27 by Théo              #+#    #+#             */
/*   Updated: 2024/07/11 04:43:15 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_command_infiles(char *cmd, int (*dst)[2])
{
	int				(*fd)[2];
	unsigned int	size;

	size = count_infile(cmd);
	fd = malloc(sizeof(int[2]) * size);
	if (!fd)
		return (-1);
	fd[0][0] = 0;
	fd[0][1] = 1;
	dst = fd;
	dst = (int (*)[2])dst;
	return (0);
}

t_command	**format_commands(int argc, char **cmd, char **envp)
{
	t_command		**commands;
	unsigned int	i;

	commands = malloc(sizeof(t_command *) * argc + 1);
	if (!commands)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		commands[i] = malloc(sizeof(t_command *));
		if (!commands[i])
			return (free_str_ptr(cmd), free_t_command(commands), NULL);
		printf("%d\n", count_infile(cmd[i]));
		commands[i]->fd = malloc(sizeof(int (*)[2]) * count_infile(cmd[i]));
		if (!commands[i]->fd)
			return (free_t_command(commands), NULL);
		set_command_infiles(cmd[i], commands[i]->fd);
		commands[i] = malloc(sizeof(t_command));
		commands[i]->command = cmd[0];
		commands[i]->options = cmd;
		//commands[i]->fd = malloc(sizeof(int[2]) * 1);
		commands[i]->envp = envp;
		i++;
	}
	commands[i] = NULL;
	envp = (char **)envp;
	return (commands);
}

t_command	**split_commands(int argc, char *argv, char **envp)
{
	t_command	**commands;
	char		**cmd_tmp;
	char		*tmp;
	int			i;

	cmd_tmp = ft_split(argv, '|');
	if (!cmd_tmp)
		return (NULL);
	i = 0;
	while (cmd_tmp[i])
	{
		tmp = cmd_tmp[i];
		cmd_tmp[i] = ft_strtrim(cmd_tmp[i], " \t");
		if (!cmd_tmp[i++])
			return (free_str_ptr(cmd_tmp), NULL);
		free(tmp);
	}
	commands = format_commands(argc, cmd_tmp, envp);
	//free_str_ptr(cmd_tmp);
	return (commands);
}
