/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:53:13 by Théo              #+#    #+#             */
/*   Updated: 2024/07/16 17:53:22 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	if (size <= 0)
		return (NULL);
	ptr = malloc(size);
	if(!ptr)
		return (NULL);
	garbage_collector(ADD, ptr);
	return (ptr);
}

void	ft_free(void *ptr)
{
	garbage_collector(DELETE, ptr);
}

void	ft_free_all()
{
	garbage_collector(CLEAR, NULL);
}
