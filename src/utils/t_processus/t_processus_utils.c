/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_processus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:01:24 by Théo              #+#    #+#             */
/*   Updated: 2024/10/05 18:01:27 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_processus_add_front(t_processus **pipes, t_processus *new)
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

void	t_processus_add_back(t_processus **pipes, t_processus *new)
{
	t_processus	*tmp;

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

t_processus	*t_processus_new(t_envp *menvp)
{
	t_processus	*new;

	new = ft_malloc(sizeof(t_processus));
	new->menvp = menvp;
	new->status_code = 0;
	new->pid = -1;
	new->parent_pid = getpid();
	new->tokens = NULL;
	new->fds[0] = 0;
	new->fds[1] = 1;
	new->here_doc[0] = -1;
	new->here_doc[1] = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*t_token_finding(t_processus *pipes, t_token_type token)
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
