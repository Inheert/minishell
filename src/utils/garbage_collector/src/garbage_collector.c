/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:01:31 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/04 12:41:07 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	malloc_error(void)
{
	printf("ERROR: a problem occured when using malloc.\n");
	ft_free_all();
	exit(EXIT_FAILURE);
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
		void *ptr, int had_to_be_free)
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
	if (had_to_be_free)
	{
		free(tmp->ptr);
		free(tmp);
	}
}

void	clear_garbage(t_ptr_stockage *container[CONTAINER_SIZE])
{
	unsigned int	i;

	if (!container)
		return ;
	i = -1;
	while (++i < CONTAINER_SIZE)
	{
		ptr_stockage_clear(&container[i]);
		container[i] = NULL;
	}
}

void	*garbage_collector(t_garbage_action action, void *ptr)
{
	static t_ptr_stockage	*container[CONTAINER_SIZE];

	if (action == ADD)
		add_to_garbage(container, ptr);
	else if (action == DELETE)
		delete_from_garbage(container, ptr, 1);
	else if (action == CLEAR)
		clear_garbage(container);
	else if (action == UNSTORE)
		delete_from_garbage(container, ptr, 0);
	return (NULL);
}
