/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:16:50 by Théo              #+#    #+#             */
/*   Updated: 2024/09/10 17:14:39 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_builtin(char *cmd)
{
	if (ft_strncmp(cmd, ECHO, 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, CD, 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, PWD, 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, EXPORT, 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, UNSET, 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, _ENV, 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, EXIT, 4) == 0)
		return (1);
	return (0);
}
