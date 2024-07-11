/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 01:28:28 by Théo              #+#    #+#             */
/*   Updated: 2024/07/11 18:26:58 by cluby            ###   ########.fr       */
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
	i = 0;
	size = str_ptr_len(ptr);
	copy = malloc(sizeof(char *) * size + 1);
	if (!copy)
		return (NULL);
	while (i < size - 1 && ptr[i])
	{
		copy[i] = ft_strdup(ptr[i]);
		if (!copy[i])
			return (free_str_ptr(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}