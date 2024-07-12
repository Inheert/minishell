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

void	free_t_token(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token)
	{
		if (token->str)
			free(token->str);
		token->str = NULL;
		tmp = token;
		token = token->next;
		free(tmp);
	}
}

void	free_t_pipe(t_pipe *pipe)
{
	t_pipe	*tmp;

	if (!pipe)
		return ;
	while (pipe)
	{
		free_t_token(pipe->tokens);
		tmp = pipe;
		pipe = pipe->next;
		free(tmp);
	}
}
