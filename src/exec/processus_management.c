/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:38:28 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/02 17:34:23 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	keep_usefull_ptr(char *cmd_path, char **cmd, char **menvp)
{
	int	i;

	ft_unstore_malloc(cmd_path);
	ft_unstore_malloc(cmd);
	ft_unstore_malloc(menvp);
	i = -1;
	while(cmd[++i])
			ft_unstore_malloc(cmd[i]);
	i = -1;
	while (menvp[++i])
			ft_unstore_malloc(menvp[i]);
	ft_free_all();
}

void	manage_execve(t_pipe *pipes, char **cmd, char **menvp)
{
	char	*cmd_path;

	cmd_path = find_path(cmd, menvp);
	if (!cmd_path)
		return (raise_error(cmd[0], "command not found", 1, 1));
	if (is_command_builtin(cmd_path))
		exec_builtins(pipes, cmd, 1);
	keep_usefull_ptr(cmd_path, cmd, menvp);
	if (execve(cmd_path, cmd, menvp) < 0)
		raise_perror("execve error", 1);
}

void	exec_first_processus(t_pipe *pipes)
{
	t_token	*token;
	char	**menvp;
	char	**cmd;

	menvp = create_str_envp(pipes->menvp);
	token_management(pipes, pipes->tokens, 1);
	if (dup2(pipes->fds[1], 1) == -1)
		raise_perror("dup2 failed", 1);
	t_pipe_close_fds(pipes);
	t_close_pipe(pipes->here_doc);
	token = t_token_finding(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found",
				"func: exec_first_processus", 1, 1));
	cmd = t_token_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL",
				"func: exec_first_processus", 1, 1));
	manage_execve(pipes, cmd, menvp);
}

void	exec_middle_processus(t_pipe *pipes)
{
	t_token	*token;
	char	**menvp;
	char	**cmd;

	menvp = create_str_envp(pipes->menvp);
	token_management(pipes, pipes->tokens, 1);
	if (pipes->here_doc[0] == -1 && dup2(pipes->prev->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	if (dup2(pipes->fds[1], 1) == -1)
		raise_perror("dup2 failed", 1);
	t_pipe_close_fds(pipes->prev);
	t_close_pipe(pipes->here_doc);
	token = t_token_finding(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found",
				"func: exec_middle_processus", 1, 1));
	cmd = t_token_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL",
				"func: exec_middle_processus", 1, 1));
	manage_execve(pipes, cmd, menvp);
}

void	exec_last_processus(t_pipe *pipes)
{
	t_token	*token;
	char	**menvp;
	char	**cmd;

	menvp = create_str_envp(pipes->menvp);
	token_management(pipes, pipes->tokens, 1);
	if (pipes->prev && dup2(pipes->prev->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	t_pipe_close_fds(pipes->prev);
	t_close_pipe(pipes->here_doc);
	token = t_token_finding(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found",
				"func: exec_last_processus", 1, 1));
	cmd = t_token_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL",
				"func: exec_last_processus", 1, 1));
	manage_execve(pipes, cmd, menvp);
}
