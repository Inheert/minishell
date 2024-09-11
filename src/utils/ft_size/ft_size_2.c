/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:51:15 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/10 16:54:15 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	fd_ptr_size(int (*fd)[2])
{
	unsigned int	size;

	if (!fd || !*fd)
		return (0);
	size = 0;
	while (fd[size])
		size++;
	return (size);
}

unsigned int	count_infile(char *s)
{
	unsigned int	i;
	unsigned int	n;

	if (!s)
		return (0);
	i = 0;
	n = 0;
	while (s[i])
		if (s[i++] == '<')
			n++;
	return (n);
}
