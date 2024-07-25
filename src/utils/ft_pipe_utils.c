/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:55:09 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/25 09:57:58 by tclaereb         ###   ########.fr       */
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

t_pipe	*ft_pipe_new(void)
{
	t_pipe	*new;

	new = ft_malloc(sizeof(t_pipe));
	new->tokens = NULL;
	new->fds[0] = 0;
	new->fds[1] = 1;
	new->redir_in = -1;
	new->redir_out = -1;
	new->standard_input = 1;
	new->standard_output = 1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*ft_find_token(t_pipe *pipes, int token)
{
	t_token	*tmp;

	if (!pipes)
		return (NULL);
	tmp = pipes->tokens;
	while (tmp && tmp->token != token)
		tmp = tmp->next;
	if (tmp->token != token)
		return (NULL);
	return (tmp);
}

int		get_actual_input(t_pipe *pipes, int set)
{
	if (pipes->standard_input)
	{
		if (set)
			pipes->standard_input = 0;
		return (0);
	}
	return (pipes->fds[0]);
}

int		get_actual_output(t_pipe *pipes, int set)
{
	if (pipes->standard_output)
	{
		if (set)
			pipes->standard_output = 0;
		return (1);
	}
	return (pipes->fds[1]);
}

void	ft_pipe_close_fds(t_pipe *pipes)
{
	if (!pipes)
		return ;
	close(pipes->fds[0]);
	close(pipes->fds[1]);
}
