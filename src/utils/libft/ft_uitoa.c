/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:56:13 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/10 16:56:13 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countsize(long n)
{
	int	count;

	if (n == 0)
		return (2);
	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	recursive(char *ptr, unsigned int n, int *i)
{
	if (n > 9)
		recursive(ptr, n / 10, i);
	ptr[*i] = n % 10 + '0';
	(*i)++;
}

char	*ft_uitoa(unsigned int n)
{
	char	*ptr;
	int		size;
	int		i;

	i = 0;
	size = countsize((long)n);
	ptr = ft_calloc(size, sizeof(char));
	recursive(ptr, n, &i);
	return (ptr);
}
