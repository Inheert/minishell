/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:19:39 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/10 17:23:31 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Why heredoc dont work good when he is part of a middle processus? What pipe create this problem? What connection/dup2 is wrong/missing?
// Is all fds are closed in the right way? Even for errors?

// First sub process write output in the standard output even if an outfile is given
// Last processus dont write output at all
void	exec_sub_processus(t_pipe *pipes, unsigned int size, unsigned int i)
{
	if (i == size)
		exec_last_processus(pipes);
	else if (i == 1)
		exec_first_processus(pipes);
	else
		exec_middle_processus(pipes);
}

void	exec_main_processus(t_pipe *pipes)
{
	t_token	*token;
	char	**cmd;

	token = t_token_finding(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found",
				"func: exec_main_processus", 1, 1));
	cmd = t_token_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL",
				"func: exec_main_processus", 1, 1));
	exec_builtins(pipes, cmd, 0);
}

void	start_execution(t_pipe *pipes)
{
	unsigned int	size;
	unsigned int	i;

	size = t_pipe_size(pipes);
	i = 1;
	if (size == 1 && t_token_finding(pipes, COMMAND)
		&& is_command_builtin(t_token_finding(pipes, COMMAND)->str))
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
			t_pipe_close_fds(pipes->prev);
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
