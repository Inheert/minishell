/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:10:34 by Théo              #+#    #+#             */
/*   Updated: 2024/08/24 16:08:15 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(char **cmd)
{
	if (!cmd || !*cmd)
		return ;
	printf("- %s\n", cmd[0]);
	if (ft_strncmp(cmd[0], ECHO, 4) == 0)
		ft_echo(cmd);
	if (ft_strncmp(cmd[0], PWD, 3) == 0)
		ft_pwd();
	if (ft_strncmp(cmd[0], CD, 2) == 0)
		ft_cd(cmd);
}
