/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:59:31 by cluby             #+#    #+#             */
/*   Updated: 2024/08/22 01:14:32 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir(t_token *token)
{
	t_token *tmp;

	if (!token)
		return ;
	tmp = token;
	if (token->str[0] == '<' || token->str[0] == '>')
	{
		if (tmp->next->token == BLANK)
			tmp = tmp->next->next;
		else
			tmp = tmp->next;
		if (tmp->token == PIPE || tmp->token == REDIR_APPEND_OUT || tmp->token == HERE_DOC || tmp->token == REDIR_IN || tmp->token == REDIR_IN)
			return  ; //bash: syntax error near unexpected token `token->str'
		tmp->token = token->token;
		tmp = token;
		token = token->next;
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		//free_one_t_token(tmp);
	}
}


void	parse_tokens(t_token *token)
{
	while (token)
	{
			printf("[%s] [%d]\n", token->str, token->token);
		if (token->token == ENV)
		{
			if (token->str[0] == '?' && token->str[1] == '\0')
				token->token = EXIT_STATUS;
		}
		redir(token);
		if (token->str[0] == '\0')
		{
			if (token->prev)
				token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			//free(token);
			//free(token->str);
		}
		token = token->next;
	}
}
