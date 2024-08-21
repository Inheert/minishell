/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:16:50 by Théo              #+#    #+#             */
/*   Updated: 2024/08/21 23:18:56 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_builtin(char *cmd)
{
	if (ft_strncmp(cmd, ECHO, 4))
		return (1);
	else if (ft_strncmp(cmd, CD, 2))
		return (1);
	else if (ft_strncmp(cmd, PWD, 3))
		return (1);
	else if (ft_strncmp(cmd, EXPORT, 6))
		return (1);
	else if (ft_strncmp(cmd, UNSET, 5))
		return (1);
	else if (ft_strncmp(cmd, _ENV, 3))
		return (1);
	else if (ft_strncmp(cmd, EXIT, 4))
		return (1);
	return (0);
}
