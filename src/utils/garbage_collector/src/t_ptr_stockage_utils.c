/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ptr_stockage_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:56:38 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/04 12:40:35 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

t_ptr_stockage	*ptr_stockage_new(void *ptr)
{
	t_ptr_stockage	*new;

	new = malloc(sizeof(t_ptr_stockage));
	if (!new)
		return (free(ptr), malloc_error(), NULL);
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
	{
		if (tmp->ptr == new->ptr)
			return (free(new));
		tmp = tmp->next;
	}
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

unsigned int	hashf(void *ptr, int size)
{
	unsigned long long	ptr_value;
	unsigned int		hash;
	size_t				i;
	size_t				s;

	ptr_value = (unsigned long long)ptr;
	i = 0;
	hash = 0;
	s = sizeof(ptr_value);
	while (i < s)
	{
		hash += ((ptr_value >> (i * 8)) & 0xFF);
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return (hash % size);
}
