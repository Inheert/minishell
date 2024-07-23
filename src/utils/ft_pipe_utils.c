/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:55:09 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/23 10:26:46 by tclaereb         ###   ########.fr       */
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

void	ft_pipe_add_front(t_pipe **pipe, t_pipe *new)
{
	if (!pipe || !new)
		return ;
	if (!*pipe)
	{
		*pipe = new;
		return ;
	}
	new->next = *pipe;
	(*pipe)->prev = new;
	*pipe = new;
}

void	ft_pipe_add_back(t_pipe **pipe, t_pipe *new)
{
	t_pipe	*tmp;

	if (!pipe || !new)
		return ;
	if (!*pipe)
	{
		*pipe = new;
		return ;
	}
	tmp = *pipe;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_pipe	*ft_pipe_new(void)
{
	t_pipe	*new;

	new = ft_malloc(sizeof(t_pipe));
	new->tokens = NULL;
	new->fds[0] = 0;
	new->fds[1] = 1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_pipe_close_fds(t_pipe *pipe)
{
	close(pipe->fds[0]);
	close(pipe->fds[1]);
}
