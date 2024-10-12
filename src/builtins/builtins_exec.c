/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:10:34 by Théo              #+#    #+#             */
/*   Updated: 2024/10/11 09:08:26 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_processus *process, char **cmd, int sub_process)
{
	if (!cmd || !*cmd)
		return ;
	if (ft_strcmp(cmd[0], _ECHO) == 0)
		ft_echo(cmd, process);
	else if (ft_strcmp(cmd[0], PWD) == 0)
		ft_pwd(process);
	else if (ft_strcmp(cmd[0], CD) == 0)
		ft_cd(*process->menvp, cmd);
	else if (ft_strcmp(cmd[0], _ENV) == 0)
		ft_env(process, *process->menvp);
	else if (ft_strcmp(cmd[0], UNSET) == 0)
		ft_unset(process->menvp, cmd + 1);
	else if (ft_strcmp(cmd[0], EXPORT) == 0)
		ft_export(cmd, process, *process->menvp);
	else if (ft_strcmp(cmd[0], EXIT) == 0)
		ft_exit(process, cmd);
	t_processus_close_builtin_fds(process);
	if (sub_process)
	{
		ft_free_all();
		exit(EXIT_SUCCESS);
	}
}
