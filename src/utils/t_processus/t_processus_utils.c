/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_processus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:01:24 by Théo              #+#    #+#             */
/*   Updated: 2024/10/06 18:08:12 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_processus_add_front(t_processus **process, t_processus *new)
{
	if (!process || !new)
		return ;
	if (!*process)
	{
		*process = new;
		return ;
	}
	new->next = *process;
	(*process)->prev = new;
	*process = new;
}

void	t_processus_add_back(t_processus **process, t_processus *new)
{
	t_processus	*tmp;

	if (!process || !new)
		return ;
	if (!*process)
	{
		*process = new;
		return ;
	}
	tmp = *process;
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
	new->heredoc[0] = -1;
	new->heredoc[1] = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*t_token_finding(t_processus *process, t_token_type token)
{
	t_token	*tmp;

	if (!process)
		return (NULL);
	tmp = process->tokens;
	while (tmp && tmp->token != token)
		tmp = tmp->next;
	if (!tmp || tmp->token != token)
		return (NULL);
	return (tmp);
}
