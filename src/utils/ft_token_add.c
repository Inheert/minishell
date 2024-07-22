/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:55:37 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/22 00:33:20 by tclaereb         ###   ########.fr       */
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

t_token	*ft_token_new(char *str, int token)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token));
	new->str = str;
	new->token = token;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*ft_token_copy(t_token *token)
{
	if (!token)
		return (NULL);
	return (ft_token_new(token->str, token->token));
}
