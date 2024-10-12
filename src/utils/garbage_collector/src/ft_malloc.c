/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:56:17 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/12 15:13:05 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	if (size <= 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (malloc_error(), NULL);
	garbage_collector(ADD, ptr);
	return (ptr);
}

static void	*copy_memory(void *dest, const void *src, size_t n)
{
	unsigned char		*_dest;
	unsigned char		*_src;

	_dest = (unsigned char *)dest;
	_src = (unsigned char *)src;
	if (_dest == NULL && _src == NULL)
		return (dest);
	while (n--)
	{
		*_dest = *_src;
		_dest++;
		_src++;
	}
	return (dest);
}

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size <= 0)
		return (ft_free(old_ptr), NULL);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (malloc_error(), NULL);
	if (old_ptr)
	{
		if (old_size < new_size)
		{
			copy_memory(new_ptr, old_ptr, old_size);
			ft_bzero(new_ptr + old_size, new_size - old_size);
		}
		else
		{
			copy_memory(new_ptr, old_ptr, new_size);
			ft_bzero(new_ptr + old_size, old_size - new_size);
		}
	}
	ft_store_malloc(new_ptr);
	ft_free(old_ptr);
	return (new_ptr);
}
