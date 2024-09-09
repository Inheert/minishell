/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:19:39 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/09 16:33:05 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Why heredoc dont work good when he is part of a middle processus? What pipe create this problem? What connection/dup2 is wrong/missing?
// Is all fds are closed in the right way? Even for errors?

void	start_execution(t_pipe *pipes)
{
	unsigned int size;
	unsigned int i;

	size = pipe_ptr_size(pipes);
	i = 1;
	if (size == 1 && ft_find_token(pipes, COMMAND) && is_command_builtin(ft_find_token(pipes, COMMAND)->str))
		return (exec_main_processus(pipes));
	while (pipes)
	{
		pipes->pid = fork();
		if (pipes->pid == -1)
			raise_perror("Fork creation failed", 1);
		if (pipes->pid == 0)
			exec_sub_processus(pipes, size, i);
		i++;
		if (pipes->prev)
			ft_pipe_close_fds(pipes->prev);
		pipes = pipes->next;
	}
}

void	ft_exec(t_token **tokens, t_envp *menvp)
{
	t_pipe			*pipes;
	t_pipe			*tmp;

	pipes = prepare_pipes(tokens, menvp);
	if (!pipes)
		return ;
	tmp = pipes;
	start_execution(pipes);
	while (tmp)
	{
		if (tmp->pid != -1 && waitpid(tmp->pid, NULL, 0) == -1)
			raise_perror("waitpid failed", 1);
		tmp = tmp->next;
	}
}
