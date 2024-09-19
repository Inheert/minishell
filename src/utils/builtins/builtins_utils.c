/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:16:50 by Théo              #+#    #+#             */
/*   Updated: 2024/09/14 18:16:58 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_builtin(char *cmd)
{
	if (ft_strcmp(cmd, ECHO) == 0)
		return (1);
	else if (ft_strcmp(cmd, CD) == 0)
		return (1);
	else if (ft_strcmp(cmd, PWD) == 0)
		return (1);
	else if (ft_strcmp(cmd, EXPORT) == 0)
		return (1);
	else if (ft_strcmp(cmd, UNSET) == 0)
		return (1);
	else if (ft_strcmp(cmd, _ENV) == 0)
		return (1);
	else if (ft_strcmp(cmd, EXIT) == 0)
		return (1);
	return (0);
}
