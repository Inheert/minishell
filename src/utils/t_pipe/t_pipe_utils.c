/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:55:09 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/10 16:45:44 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_pipe_add_front(t_pipe **pipes, t_pipe *new)
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

void	t_pipe_add_back(t_pipe **pipes, t_pipe *new)
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

t_pipe	*t_pipe_new(t_envp *menvp)
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

t_token	*t_token_finding(t_pipe *pipes, e_token token)
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
