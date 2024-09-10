/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:43:06 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/10 16:46:07 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_pipe_display(t_pipe *pipes)
{
	while (pipes)
	{
		while (pipes->tokens)
		{
			printf("%s ", pipes->tokens->str);
			pipes->tokens = pipes->tokens->next;
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
