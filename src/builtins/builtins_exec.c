/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:10:34 by Théo              #+#    #+#             */
/*   Updated: 2024/10/02 16:01:27 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_exit(cmd);
	if (sub_process)
	{
		ft_free_all();
		exit(EXIT_SUCCESS);
	}
}
