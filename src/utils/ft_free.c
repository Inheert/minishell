/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 01:28:23 by Théo              #+#    #+#             */
/*   Updated: 2024/07/11 01:28:23 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *ptr, size_t size)
{
	if (!ptr)
		return ;
	ft_bzero(ptr, size);
	free(ptr);
}

void	free_str_ptr(char **ptr)
{
	size_t	i;
	size_t	size;

	if (!ptr || !*ptr)
		return ;
	i = -1;
	size = str_ptr_len(ptr);
	while (++i < size && ptr[i])
		ft_free(ptr[i], ft_strlen(ptr[i]));
	ft_free(ptr, str_ptr_len(ptr));
}

void	free_t_token(t_token **token)
{
	t_token	*tmp;
	t_token *free_tmp;

	tmp = *token;
	while (tmp)
	{
		free(tmp->str);
		tmp->str = NULL;
		free_tmp = tmp;
		tmp = tmp->next;
		free(free_tmp);
	}
	*token = NULL;
}
