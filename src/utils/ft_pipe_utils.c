/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:09:55 by Théo              #+#    #+#             */
/*   Updated: 2024/07/12 02:08:30 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_pipe	*ft_pipe_new(t_token **token)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->tokens = token;
	new->fds[0] = 0;
	new->fds[1] = 1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
