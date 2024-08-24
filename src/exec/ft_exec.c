/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:19:39 by tclaereb          #+#    #+#             */
/*   Updated: 2024/08/24 16:44:28 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Why heredoc dont work good when he is part of a middle processus? What pipe create this problem? What connection/dup2 is wrong/missing?
// Is all fds are closed in the right way? Even for errors?

void	start_execution(t_pipe *pipes, char **envp)
{
	unsigned int size;
	unsigned int i;

	size = pipe_ptr_size(pipes);
	i = 1;
	if (size == 1 && ft_find_token(pipes, COMMAND) && is_command_builtin(ft_find_token(pipes, COMMAND)->str))
		return (exec_main_processus(pipes, envp));
	while (pipes)
	{
		pipes->pid = fork();
		if (pipes->pid == -1)
			raise_perror("Fork creation failed", 1);
		if (pipes->pid == 0)
			exec_sub_processus(pipes, size, i, envp);
		i++;
		if (pipes->prev)
			ft_pipe_close_fds(pipes->prev);
		pipes = pipes->next;
	}
}

void	ft_exec(t_token **tokens, char **envp)
{
	t_pipe			*pipes;
	t_pipe			*tmp;

	pipes = prepare_pipes(tokens);
	if (!pipes)
		return ;
	tmp = pipes;
	start_execution(pipes, envp);
	while (tmp)
	{
		if (waitpid(tmp->pid, NULL, 0) == -1)
			raise_perror("waitpid failed", 1);
		tmp = tmp->next;
	}
}
