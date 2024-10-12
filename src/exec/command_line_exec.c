/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 01:34:58 by Théo              #+#    #+#             */
/*   Updated: 2024/10/11 19:16:38 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Init children signal and execute sub-processus
static void	exec_sub_processus(t_processus *process, unsigned int size,
								unsigned int i)
{
	set_signals(FORK);
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

	token = t_token_finding(process->tokens, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found",
				"func: exec_main_processus", 1, 1));
	token_management(process, process->tokens, 0);
	delete_useless_tokens(process);
	cmd = t_token_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL",
				"func: exec_main_processus", 1, 1));
	exec_builtins(process, cmd, 0);
}

// Function used to create sub-processus (fork) or to execute builtin
// on the main processus.
static int	start_execution(t_processus *process)
{
	t_processus		*tmp;
	unsigned int	size;
	unsigned int	i;

	size = t_processus_size(process);
	i = 1;
	if (size == 1 && t_token_finding(process->tokens, COMMAND)
		&& is_command_builtin(t_token_finding(process->tokens, COMMAND)->str))
		return (exec_main_processus(process), 1);
	tmp = process;
	while (process)
	{
		set_signals(FORK);
		process->pid = fork();
		if (process->pid == -1)
			raise_perror("Fork creation failed", 1);
		if (process->pid == 0)
			exec_sub_processus(process, size, i);
		i++;
		process = process->next;
	}
	t_processus_close_fds(tmp);
	return (0);
}

static void	signal_handler(void)
{
	if (g_signal_code == SIGQUIT)
		ft_putendl_fd("^\\Quit", STDERR_FILENO);
	else if (g_signal_code == SIGINT)
		ft_putendl_fd("^C", STDERR_FILENO);
	g_signal_code = 0;
}

void	command_line_exec(t_token **tokens, t_envp **menvp)
{
	t_processus			*process;
	t_processus			*tmp;
	int					exit_status;

	process = prepare_processus(tokens, menvp);
	if (!process)
		return ;
	if (does_fds_count_exceed_the_limit(process))
		return (raise_error("fds",
				"you can't open more than 1024 fds (see ulimit -a).", 0, 1));
	manage_heredocs(process);
	exit_status = 0;
	tmp = process;
	if (start_execution(process))
		return ;
	while (tmp)
	{
		waitpid(tmp->pid, &exit_status, 0);
		tmp = tmp->next;
		if (WIFEXITED(exit_status))
			set_exit_status(WEXITSTATUS(exit_status), NULL);
	}
	signal_handler();
}
