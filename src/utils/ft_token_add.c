/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:32:52 by Théo              #+#    #+#             */
/*   Updated: 2024/07/12 03:05:01 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_add_front(t_token **token, t_token *new)
{
	if (!token || !new)
		return ;
	if (!*token)
	{
		*token = new;
		return ;
	}
	new->next = *token;
	(*token)->prev = new;
	*token = new;
}

void	ft_token_add_back(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!token || !new)
		return ;
	if (!*token)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_token	*ft_token_copy(t_token *token)
{
	t_token	*copy;

	if (!token)
		return (NULL);
	copy = malloc(sizeof(t_token));
	if (!copy)
		return (NULL);
	copy->str = ft_strdup(token->str);
	if (!copy->str)
		return (free(copy), NULL);
	copy->token = token->token;
	copy->next = NULL;
	copy->prev = NULL;
	return (copy);
}

t_token	*ft_token_n_copy(t_token *token, unsigned int n)
{
	t_token	*copy;
	t_token	*tmp;

	if (!token)
		return (NULL);
	copy = ft_token_copy(token);
	if (!copy)
		return (NULL);
	copy = copy->next;
	while (n-- && token)
	{
		tmp = ft_token_copy(token);
		if (!tmp)
			return (free_t_token(copy), NULL);
		token = token->next;
	}
	return (copy);
}

t_token	*ft_token_new(char *str, int token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->token = token;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
