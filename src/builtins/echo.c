/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:27 by Théo              #+#    #+#             */
/*   Updated: 2024/09/10 16:54:00 by tclaereb         ###   ########.fr       */
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
	size = str_ptr_size(cmd);
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
