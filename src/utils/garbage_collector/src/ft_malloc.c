/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:53:13 by Théo              #+#    #+#             */
/*   Updated: 2024/07/16 17:58:34 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	malloc_error()
{
	printf("ERROR: a problem occured when using malloc.\n");
	ft_free_all();
	exit(EXIT_FAILURE);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	if (size <= 0)
		return (NULL);
	ptr = malloc(size);
	if(!ptr)
		return (malloc_error(), NULL);
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
