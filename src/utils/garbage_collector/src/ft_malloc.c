/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:56:17 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/21 23:56:19 by tclaereb         ###   ########.fr       */
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
