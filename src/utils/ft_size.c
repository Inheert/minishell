/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 01:28:16 by Théo              #+#    #+#             */
/*   Updated: 2024/07/11 01:28:16 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	token_ptr_size(t_token *token)
{
	unsigned int size;

	if (!token)
		return (0);
	size = 0;
	while (token && size++)
		token = token->next;
	return (size);
}

unsigned int	str_ptr_len(char **ptr)
{
	unsigned int	size;

	if (!ptr || !*ptr)
		return (0);
	size = 0;
	while (ptr[size])
		size++;
	return (size);
}

unsigned int	fd_ptr_len(int (*fd)[2])
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
