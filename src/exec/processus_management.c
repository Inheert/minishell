/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:38:28 by tclaereb          #+#    #+#             */
/*   Updated: 2024/08/26 08:36:11 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	exec_first_processus(t_pipe *pipes, char **envp)
{
	t_token	*token;
	char	**cmd;
	char	*cmd_path;

	token_management(pipes, pipes->tokens);
	if (dup2(pipes->fds[1], 1) == -1)
		raise_perror("dup2 failed", 1);
	ft_pipe_close_fds(pipes);
	ft_close_pipe(pipes->here_doc);
	token = ft_find_token(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found",
				"func: exec_first_processus", 1, 1));
	cmd = token_struct_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL",
				"func: exec_first_processus", 1, 1));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (raise_error(cmd[0], "command not found", 1, 1));
	if (is_command_builtin(cmd_path))
		exec_builtins(pipes, cmd);
	if (execve(cmd_path, cmd, envp) == -1)
		raise_perror("execve error", 1);
}

void	exec_middle_processus(t_pipe *pipes, char **envp)
{
	t_token	*token;
	char	**cmd;
	char	*cmd_path;

	token_management(pipes, pipes->tokens);
	if (pipes->here_doc[0] == -1 && dup2(pipes->prev->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	if (dup2(pipes->fds[1], 1) == -1)
		raise_perror("dup2 failed", 1);
	ft_pipe_close_fds(pipes);
	ft_pipe_close_fds(pipes->prev);
	ft_close_pipe(pipes->here_doc);
	token = ft_find_token(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found",
				"func: exec_middle_processus", 1, 1));
	cmd = token_struct_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL",
				"func: exec_middle_processus", 1, 1));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (raise_error(cmd[0], "command not found", 1, 1));
	if (is_command_builtin(cmd_path))
		exec_builtins(pipes, cmd);
	if (execve(cmd_path, cmd, envp) == -1)
		raise_perror("execve error", 1);
}

void	exec_last_processus(t_pipe *pipes, char **envp)
{
	t_token	*token;
	char	**cmd;
	char	*cmd_path;

	token_management(pipes, pipes->tokens);
	if (pipes->prev && dup2(pipes->prev->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	ft_pipe_close_fds(pipes->prev);
	ft_close_pipe(pipes->here_doc);
	token = ft_find_token(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found",
				"func: exec_last_processus", 1, 1));
	cmd = token_struct_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL",
				"func: exec_last_processus", 1, 1));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (raise_error(cmd[0], "command not found", 1, 1));
	if (is_command_builtin(cmd_path))
		exec_builtins(pipes, cmd);
	if (execve(cmd_path, cmd, envp) == -1)
		raise_perror("execve error", 1);
}

// First sub process write output in the standard output even if an outfile is given
// Last processus dont write output at all
void	exec_sub_processus(t_pipe *pipes, unsigned int size, unsigned int i, char **envp)
{
	if (i == size)
		exec_last_processus(pipes, envp);
	else if (i == 1)
		exec_first_processus(pipes, envp);
	else
		exec_middle_processus(pipes, envp);
}

void	exec_main_processus(t_pipe *pipes, char **envp)
{
	t_token	*token;
	char	**cmd;

	envp = (char **)envp;
	token = ft_find_token(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found", "func: exec_main_processus", 1, 1));
	cmd = token_struct_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL", "func: exec_main_processus", 1, 1));
	exec_builtins(pipes, cmd);
}
