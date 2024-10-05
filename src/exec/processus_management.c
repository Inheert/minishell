/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:38:28 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/05 23:32:05 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	store_unstore_malloc(char *cmd_path, char **cmd, char **menvp,
// 		int to_store)
// {
// 	int	i;

// 	if (!to_store)
// 	{
// 		ft_unstore_malloc(cmd_path);
// 		ft_unstore_malloc(cmd);
// 		ft_unstore_malloc(menvp);
// 		i = -1;
// 		while (cmd[++i])
// 			ft_unstore_malloc(cmd[i]);
// 		i = -1;
// 		while (menvp[++i])
// 			ft_unstore_malloc(menvp[i]);
// 		return ;
// 	}
// 	ft_store_malloc(cmd_path);
// 	ft_store_malloc(cmd);
// 	ft_store_malloc(menvp);
// 	i = -1;
// 	while (cmd[++i])
// 		ft_store_malloc(cmd[i]);
// 	i = -1;
// 	while (menvp[++i])
// 		ft_store_malloc(menvp[i]);
// }

static void	manage_execve(t_processus *pipes, char **cmd, char **menvp)
{
	char	*cmd_path;

	cmd_path = find_path(cmd, menvp);
	if (!cmd_path)
		return (raise_error(cmd[0], "command not found", 1, 127));
	if (is_command_builtin(cmd_path))
		exec_builtins(pipes, cmd, 1);
	if (execve(cmd_path, cmd, menvp) < 0)
		return (raise_perror("execve error", 1));
}

void	exec_first_processus(t_processus *pipes)
{
	t_token	*token;
	char	**menvp;
	char	**cmd;

	menvp = t_envp_convert_to_str(pipes->menvp);
	token_management(pipes, pipes->tokens, 1);
	if (dup2(pipes->fds[1], 1) == -1)
		raise_perror("dup2 failed", 1);
	t_processus_close_fds(pipes);
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

void	exec_middle_processus(t_processus *pipes)
{
	t_token	*token;
	char	**menvp;
	char	**cmd;

	menvp = t_envp_convert_to_str(pipes->menvp);
	token_management(pipes, pipes->tokens, 1);
	if (pipes->here_doc[0] == -1 && pipes->fds[0] == -1
		&& dup2(pipes->prev->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	else if (pipes->here_doc[0] == -1 && pipes->fds[0] != -1
		&& dup2(pipes->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	if (dup2(pipes->fds[1], 1) == -1)
		raise_perror("dup2 failed", 1);
	t_processus_close_fds(pipes);
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

void	exec_last_processus(t_processus *pipes)
{
	t_token	*token;
	char	**menvp;
	char	**cmd;

	menvp = t_envp_convert_to_str(pipes->menvp);
	token_management(pipes, pipes->tokens, 1);
	if (pipes->here_doc[0] == -1 && pipes->fds[0] == 0
		&& pipes->prev && dup2(pipes->prev->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	t_processus_close_fds(pipes);
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
