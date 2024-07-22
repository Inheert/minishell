/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:55:52 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/21 23:55:54 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_str_ptr(char **ptr)
{
	char	**copy;
	size_t	size;
	size_t	i;

	if (!ptr || !*ptr)
		return (NULL);
	i = -1;
	size = str_ptr_len(ptr);
	copy = ft_malloc(sizeof(char *) * size + 1);
	while (++i < size - 1 && ptr[i])
		copy[i] = ft_strdup(ptr[i]);
	copy[i] = NULL;
	return (copy);
}
