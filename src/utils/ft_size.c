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

#include "../../includes/minishell.h"

size_t	str_ptr_len(char **ptr)
{
	size_t	size;

	if (!ptr || !*ptr)
		return (0);
	size = 0;
	while (ptr[size])
		size++;
	return (size);
}

size_t	t_command_len(t_command **commands)
{
	size_t	size;

	if (!commands || !*commands)
		return (0);
	size = 0;
	while (commands[size])
		size++;
	return (size);
}
