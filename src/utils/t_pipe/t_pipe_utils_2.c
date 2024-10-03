/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:43:06 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/03 13:22:44 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_pipe_display(t_pipe *pipes)
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

void	t_pipe_close_fds(t_pipe *pipes)
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
		pipes = pipes->next;
	}
}

void	t_pipe_close_builtin_fds(t_pipe *pipes)
{
	int	fd;

	fd = get_fds(pipes, STDOUT_FILENO);
	if (fd != 1 && fd != -1)
		close(fd);
	fd = get_fds(pipes, STDIN_FILENO);
	if (fd != 0 && fd != -1)
		close(fd);
}

void	t_close_pipe(int fd[2])
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}

int	get_fds(t_pipe *pipes, int fd)
{
	printf("");
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
