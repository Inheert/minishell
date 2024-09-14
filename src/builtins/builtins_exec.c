/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:10:34 by Théo              #+#    #+#             */
/*   Updated: 2024/09/14 18:21:05 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_pipe *pipes, char **cmd, int sub_process)
{
	if (!cmd || !*cmd)
		return ;
	else if (ft_strcmp(cmd[0], ECHO) == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], PWD) == 0)
		ft_pwd();
	else if (ft_strcmp(cmd[0], CD) == 0)
		ft_cd(pipes->menvp, cmd);
	else if (ft_strcmp(cmd[0], _ENV) == 0)
		ft_env(pipes->menvp);
	else if (ft_strcmp(cmd[0], UNSET) == 0)
		ft_unset(pipes->menvp, cmd[1]);
	else if (ft_strcmp(cmd[0], EXPORT) == 0)
		ft_export(cmd, pipes->menvp);
	else if (ft_strcmp(cmd[0], EXIT) == 0)
		ft_exit(cmd);
	if (sub_process)
	{
		ft_free_all();
		exit(EXIT_SUCCESS);
	}
}
