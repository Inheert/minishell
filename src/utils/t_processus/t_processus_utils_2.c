/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_processus_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:01:32 by Théo              #+#    #+#             */
/*   Updated: 2024/10/06 01:18:35 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_processus_display(t_processus *process)
{
	t_token	*tmp;

	while (process)
	{
		tmp = process->tokens;
		while (tmp)
		{
			printf("%s ", tmp->str);
			tmp = tmp->next;
		}
		printf("\n");
		process = process->next;
	}
}

void	t_processus_close_fds(t_processus *process)
{
	if (!process)
		return ;
	while (process->prev)
		process = process->prev;
	while (process)
	{
		if (process->fds[0] != 0 && process->fds[0] != -1)
			close(process->fds[0]);
		if (process->fds[1] != 1 && process->fds[1] != -1)
			close(process->fds[1]);
		if (process->here_doc[0] != -1)
			close(process->here_doc[0]);
		if (process->here_doc[1] != -1)
			close(process->here_doc[1]);
		process->fds[0] = -1;
		process->fds[1] = -1;
		process->here_doc[0] = -1;
		process->here_doc[1] = -1;
		process = process->next;
	}
}

void	t_processus_close_builtin_fds(t_processus *process)
{
	int	fd;

	if (!process)
		return ;
	fd = get_fds(process, STDOUT_FILENO);
	if (fd != 1 && fd != -1)
		close(fd);
	fd = get_fds(process, STDIN_FILENO);
	if (fd != 0 && fd != -1)
		close(fd);
}

int	get_fds(t_processus *process, int fd)
{
	if (fd == 0)
	{
		if (!process)
			return (0);
		if (process->fds[0] == -1)
			return (0);
		return (process->fds[0]);
	}
	else if (fd == 1)
	{
		if (!process)
			return (1);
		if (process->fds[1] == -1)
			return (1);
		return (process->fds[1]);
	}
	return (-1);
}
