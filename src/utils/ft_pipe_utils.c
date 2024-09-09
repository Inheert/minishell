/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:55:09 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/08 15:38:46 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_display(t_pipe *pipes)
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

void	ft_pipe_add_front(t_pipe **pipes, t_pipe *new)
{
	if (!pipes || !new)
		return ;
	if (!*pipes)
	{
		*pipes = new;
		return ;
	}
	new->next = *pipes;
	(*pipes)->prev = new;
	*pipes = new;
}

void	ft_pipe_add_back(t_pipe **pipes, t_pipe *new)
{
	t_pipe	*tmp;

	if (!pipes || !new)
		return ;
	if (!*pipes)
	{
		*pipes = new;
		return ;
	}
	tmp = *pipes;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	if (new->prev)
		if (pipe(new->prev->fds) == -1)
			raise_perror("Pipe creation failed", 1);
}

t_pipe	*ft_pipe_new(t_envp *menvp)
{
	t_pipe	*new;

	new = ft_malloc(sizeof(t_pipe));
	new->menvp = menvp;
	new->pid = -1;
	new->tokens = NULL;
	new->fds[0] = 0;
	new->fds[1] = 1;
	new->here_doc[0] = -1;
	new->here_doc[1] = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*ft_find_token(t_pipe *pipes, e_token token)
{
	t_token	*tmp;

	if (!pipes)
		return (NULL);
	tmp = pipes->tokens;
	while (tmp && tmp->token != token)
		tmp = tmp->next;
	if (!tmp || tmp->token != token)
		return (NULL);
	return (tmp);
}

void	ft_pipe_close_fds(t_pipe *pipes)
{
	if (!pipes)
		return ;
	close(pipes->fds[0]);
	close(pipes->fds[1]);
}

void	ft_close_pipe(int fd[2])
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}
