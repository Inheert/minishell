/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:32:52 by Théo              #+#    #+#             */
/*   Updated: 2024/07/11 18:52:37 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

	new = malloc(sizeof(t_token *));
	if (!new)
		return (NULL);
	new->str = str;
	new->token = token;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
