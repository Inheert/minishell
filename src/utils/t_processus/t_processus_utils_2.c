/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_processus_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:01:32 by Théo              #+#    #+#             */
/*   Updated: 2024/10/05 18:01:36 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_processus_display(t_processus *pipes)
{
	t_token	*tmp;

	while (pipes)
	{
		tmp = pipes->tokens;
		while (tmp)
		{
			printf("%s ", tmp->str);
			tmp = tmp->next;
		}
		printf("\n");
		pipes = pipes->next;
	}
}

void	t_processus_close_fds(t_processus *pipes)
{
	if (!pipes)
		return ;
	while (pipes->prev)
		pipes = pipes->prev;
	while (pipes)
	{
		if (pipes->fds[0] != 0 && pipes->fds[0] != -1)
			close(pipes->fds[0]);
		if (pipes->fds[1] != 1 && pipes->fds[1] != -1)
			close(pipes->fds[1]);
		if (pipes->here_doc[0] != -1)
			close(pipes->here_doc[0]);
		if (pipes->here_doc[1] != -1)
			close(pipes->here_doc[1]);
		pipes->fds[0] = -1;
		pipes->fds[1] = -1;
		pipes->here_doc[0] = -1;
		pipes->here_doc[1] = -1;
		pipes = pipes->next;
	}
}

void	t_processus_close_builtin_fds(t_processus *pipes)
{
	int	fd;

	if (!pipes)
		return ;
	fd = get_fds(pipes, STDOUT_FILENO);
	if (fd != 1 && fd != -1)
		close(fd);
	fd = get_fds(pipes, STDIN_FILENO);
	if (fd != 0 && fd != -1)
		close(fd);
}

int	get_fds(t_processus *pipes, int fd)
{
	if (fd == 0)
	{
		if (!pipes)
			return (0);
		if (pipes->fds[0] == -1)
			return (0);
		return (pipes->fds[0]);
	}
	else if (fd == 1)
	{
		if (!pipes)
			return (1);
		if (pipes->fds[1] == -1)
			return (1);
		return (pipes->fds[1]);
	}
	return (-1);
}
