/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:19:39 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/04 16:22:49 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Why heredoc dont work good when he is part of a middle processus?
// What pipe create this problem? What connection/dup2 is wrong/missing?
// Is all fds are closed in the right way? Even for errors?

void	exec_sub_processus(t_pipe *pipes, unsigned int size, unsigned int i)
{
	init_children_signals_handlers();
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
	t_pipe			*tmp;
	unsigned int	size;
	unsigned int	i;

	size = t_pipe_size(pipes);
	i = 1;
	if (size == 1 && t_token_finding(pipes, COMMAND)
		&& is_command_builtin(t_token_finding(pipes, COMMAND)->str))
		return (exec_main_processus(pipes));
	tmp = pipes;
	while (pipes)
	{
		pipes->pid = fork();
		if (pipes->pid == -1)
			raise_perror("Fork creation failed", 1);
		if (pipes->pid == 0)
			exec_sub_processus(pipes, size, i);
		i++;
		pipes = pipes->next;
	}
	init_silence_signals_handlers();
	t_pipe_close_fds(tmp);
}

int	ft_exec(t_token **tokens, t_envp *menvp)
{
	t_pipe			*pipes;
	t_pipe			*tmp;
	int				exit_status;

	pipes = prepare_pipes(tokens, menvp);
	if (!pipes)
		return (0);
	exit_status = 0;
	tmp = pipes;
	start_execution(pipes);
	while (tmp)
	{
		if (tmp->pid != -1 && waitpid(tmp->pid, &exit_status, 0) == -1)
			raise_perror("waitpid failed", 1);
		tmp = tmp->next;
	}
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (0);
}
