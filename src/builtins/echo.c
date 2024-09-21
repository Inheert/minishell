/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:27 by Théo              #+#    #+#             */
/*   Updated: 2024/09/20 12:00:30 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_echo_arg(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0 && str[i] != '-')
			return (0);
		else if (i != 0 && str[i] != 'n')
			return (0);
	}
	if (i > 0 && str[i - 1] == '-')
		return (0);
	return (1);
}

void	ft_echo(char **cmd)
{
	int	line_break;
	int	line_break_valid;
	int	i;

	line_break = 1;
	line_break_valid = 1;
	i = 0;
	while (cmd[++i])
	{
		if (line_break_valid && is_echo_arg(cmd[i]))
		{
			line_break = 0;
			continue ;
		}
		else
			line_break_valid = 0;
		printf("%s", cmd[i]);
	}
	if (line_break)
		printf("\n");
}
