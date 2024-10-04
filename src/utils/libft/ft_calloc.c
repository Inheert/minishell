/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:20:37 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/04 13:03:27 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	size_max;

	size_max = (size_t)-1;
	if (nmemb == 0 || size == 0)
		return (NULL);
	if (size != 0)
		if (nmemb > size_max / size)
			return (NULL);
	ptr = (char *)ft_malloc(size * nmemb);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
