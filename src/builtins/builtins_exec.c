/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:10:34 by Théo              #+#    #+#             */
/*   Updated: 2024/09/10 17:23:01 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_pipe *pipes, char **cmd, int sub_process)
{
	if (!cmd || !*cmd)
		return ;
	else if (ft_strncmp(cmd[0], ECHO, 4) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd[0], PWD, 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd[0], CD, 2) == 0)
		ft_cd(cmd);
	else if (ft_strncmp(cmd[0], _ENV, 3) == 0)
		ft_env(pipes->menvp);
	else if (ft_strncmp(cmd[0], UNSET, 5) == 0)
		ft_unset(pipes->menvp, cmd[1]);
	else if (ft_strncmp(cmd[0], EXPORT, 6) == 0)
		ft_export(cmd, pipes->menvp);
	if (sub_process)
		exit(EXIT_SUCCESS);
}
