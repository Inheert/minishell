/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:01:31 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/10 16:58:04 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

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

void	add_to_garbage(t_ptr_stockage *container[CONTAINER_SIZE], void *ptr)
{
	t_ptr_stockage	*new;
	unsigned int	index;

	if (!ptr)
		return ;
	new = ptr_stockage_new(ptr);
	index = hashf(ptr, CONTAINER_SIZE);
	if (container[index])
		ptr_stockage_add_back(&container[index], new);
	else
		container[index] = new;
}

void	delete_from_garbage(t_ptr_stockage *container[CONTAINER_SIZE],
		void *ptr)
{
	t_ptr_stockage	*tmp;
	unsigned int	index;

	if (!ptr)
		return ;
	index = hashf(ptr, CONTAINER_SIZE);
	if (!container[index])
		return ;
	tmp = container[index];
	while (tmp && tmp->ptr != ptr)
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp == container[index])
		container[index] = container[index]->next;
	free(tmp->ptr);
	free(tmp);
}

void	clear_garbage(t_ptr_stockage *container[CONTAINER_SIZE])
{
	unsigned int	i;

	if (!container)
		return ;
	i = 0;
	while (i < CONTAINER_SIZE)
		ptr_stockage_clear(&container[i++]);
}

void	*garbage_collector(t_garbage_action action, void *ptr)
{
	static t_ptr_stockage	*container[CONTAINER_SIZE];

	if (action == ADD)
		add_to_garbage(container, ptr);
	else if (action == DELETE)
		delete_from_garbage(container, ptr);
	else if (action == CLEAR)
		clear_garbage(container);
	return (NULL);
}
