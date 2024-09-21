/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:43:06 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/21 10:55:27 by tclaereb         ###   ########.fr       */
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

void	t_close_pipe(int fd[2])
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}
