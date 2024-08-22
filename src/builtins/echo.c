/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:27 by Théo              #+#    #+#             */
/*   Updated: 2024/08/22 02:25:37 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd)
{
	char			**tmp;
	unsigned int	size;
	unsigned int	new_line;

	if (!cmd)
		return ;
	size = str_ptr_len(cmd);
	if (size == 1)
		printf("\n");
	if (size > 1)
	{
		new_line = 1;
		tmp = cmd;
		tmp++;
		if (ft_strncmp(*tmp, "-n", 2) == 0 && *tmp)
		{
			new_line = 0;
			tmp++;
		}
		while (*tmp)
		{
			write(1, *tmp, ft_strlen(*tmp));
			tmp++;
			if (*tmp)
				write(1, " ", 1);
		}
		if (new_line)
			write(1, "\n", 1);
	}
	ft_free_all();
	exit(EXIT_SUCCESS);
}
