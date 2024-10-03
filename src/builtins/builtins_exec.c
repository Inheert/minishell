/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:10:34 by Théo              #+#    #+#             */
/*   Updated: 2024/10/03 13:23:56 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_sub_processus_exit(int sub_process)
{
	if (sub_process)
	{
		ft_free_all();
		exit(EXIT_SUCCESS);
	}
}

void	exec_builtins(t_pipe *pipes, char **cmd, int sub_process)
{
	if (!cmd || !*cmd)
		return ;
	token_management(pipes, pipes->tokens, 0);
	if (ft_strcmp(cmd[0], ECHO) == 0)
		ft_echo(cmd, pipes);
	else if (ft_strcmp(cmd[0], PWD) == 0)
		ft_pwd(pipes);
	else if (ft_strcmp(cmd[0], CD) == 0)
		ft_cd(pipes->menvp, cmd);
	else if (ft_strcmp(cmd[0], _ENV) == 0)
		ft_env(pipes, pipes->menvp);
	else if (ft_strcmp(cmd[0], UNSET) == 0)
		ft_unset(pipes->menvp, cmd[1]);
	else if (ft_strcmp(cmd[0], EXPORT) == 0)
		ft_export(cmd, pipes, pipes->menvp);
	else if (ft_strcmp(cmd[0], EXIT) == 0)
		ft_exit(pipes, cmd);
	t_pipe_close_builtin_fds(pipes);
	manage_sub_processus_exit(sub_process);
}
