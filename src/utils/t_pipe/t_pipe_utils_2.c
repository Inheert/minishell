/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:43:06 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/20 11:27:41 by Théo             ###   ########.fr       */
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
	close(pipes->fds[0]);
	close(pipes->fds[1]);
}

void	t_close_pipe(int fd[2])
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}
