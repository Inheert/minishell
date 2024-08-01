/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:59:31 by cluby             #+#    #+#             */
/*   Updated: 2024/08/02 01:05:11 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_word_token(t_token *token)
{
	token->str = first_word_next_token(token);
	if (!token->str)
		return ;	//ERROR
}

static void	redir(t_token *token)
{
	if (token->str[0] == '<' || token->str[0] == '>')
	{
		first_word_token(token);
		token->next->str = delete_first_word(token->next->str);
	}
}

void	parse_tokens(t_token *token)
{
	while (token)
	{
		if (token->token == ENV)
		{
			token->token = EXIT_STATUS;
		}
		redir(token);
		if (token->str[0] == '\0')
		{
			if (token->prev)
				token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			free(token->str);
			free(token);
		}
		token = token->next;
	}
}
