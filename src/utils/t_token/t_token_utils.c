/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:32:52 by Théo              #+#    #+#             */
/*   Updated: 2024/10/06 17:59:11 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_token_add_front(t_token **token, t_token *new)
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

void	t_token_add_back(t_token **token, t_token *new)
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

t_token	*t_token_new(char *str, int token)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token));
	new->str = str;
	new->token = token;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	t_token_del(t_token **tokens, t_token *del)
{
	if (!tokens || !*tokens || !del)
		return ;
	if (del == *tokens)
	{
		*tokens = (*tokens)->next;
		if (*tokens)
			(*tokens)->prev = NULL;
	}
	else
	{
		if (del->prev)
			del->prev->next = del->next;
		if (del->next)
			del->next->prev = del->prev;
		else
			del->prev->next = NULL;
	}
	free_one_t_token(del);
}

t_token	*t_token_copy(t_token *token)
{
	if (!token)
		return (NULL);
	return (t_token_new(ft_strdup(token->str), token->token));
}
