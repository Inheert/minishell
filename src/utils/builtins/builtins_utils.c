/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:16:50 by Théo              #+#    #+#             */
/*   Updated: 2024/08/22 01:46:44 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_builtin(char *cmd)
{
	printf("%s %d\n", cmd, ft_strncmp(cmd, "echd", 4) == 0);
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
