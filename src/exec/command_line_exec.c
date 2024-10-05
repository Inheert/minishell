/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 01:34:58 by Théo              #+#    #+#             */
/*   Updated: 2024/10/06 01:35:00 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Init children signal and execute sub-processus
static void	exec_sub_processus(t_processus *process, unsigned int size,
								unsigned int i)
{
	init_children_signals_handlers();
	if (i == size)
		exec_last_processus(process);
	else if (i == 1)
		exec_first_processus(process);
	else
		exec_middle_processus(process);
}

// Parse token, create char ** command + arg and execute builtin on the main
// processus.
static void	exec_main_processus(t_processus *process)
{
	t_token	*token;
	char	**cmd;

	token = t_token_finding(process, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found",
				"func: exec_main_processus", 1, 1));
	cmd = t_token_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL",
				"func: exec_main_processus", 1, 1));
	exec_builtins(process, cmd, 0);
}

// Function used to create sub-processus (fork) or to execute builtin
// on the main processus.
static void	start_execution(t_processus *process)
{
	t_processus		*tmp;
	unsigned int	size;
	unsigned int	i;

	size = t_processus_size(process);
	i = 1;
	if (size == 1 && t_token_finding(process, COMMAND)
		&& is_command_builtin(t_token_finding(process, COMMAND)->str))
		return (exec_main_processus(process));
	tmp = process;
	while (process)
	{
		process->pid = fork();
		if (process->pid == -1)
			raise_perror("Fork creation failed", 1);
		if (process->pid == 0)
			exec_sub_processus(process, size, i);
		i++;
		process = process->next;
	}
	init_silence_signals_handlers();
	t_processus_close_fds(tmp);
}

int	command_line_exec(t_token **tokens, t_envp *menvp)
{
	t_processus			*process;
	t_processus			*tmp;
	int					exit_status;

	process = prepare_processus(tokens, menvp);
	ft_heredocs(process);
	if (!process)
		return (0);
	exit_status = 0;
	tmp = process;
	start_execution(process);
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
