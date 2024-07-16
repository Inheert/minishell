/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ptr_stockage_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:50:44 by Théo              #+#    #+#             */
/*   Updated: 2024/07/16 17:50:57 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

t_ptr_stockage	*ptr_stockage_new(void *ptr)
{
	t_ptr_stockage	*new;

	new = malloc(sizeof(t_ptr_stockage));
	if (!new)
		return (NULL);
	new->ptr = ptr;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ptr_stockage_add_back(t_ptr_stockage **storage, t_ptr_stockage *new)
{
	t_ptr_stockage	*tmp;

	if (!storage || !new)
		return ;
	if (!*storage)
	{
		*storage = new;
		return ;
	}
	tmp = *storage;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;	
}

void	ptr_stockage_clear(t_ptr_stockage **storage)
{
	t_ptr_stockage	*tmp;

	if (!storage ||!*storage)
		return ;
	while (*storage)
	{
		tmp = *storage;
		*storage = (*storage)->next;
		free(tmp->ptr);
		free(tmp);
	}
}
