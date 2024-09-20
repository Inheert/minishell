/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:59:31 by cluby             #+#    #+#             */
/*   Updated: 2024/09/19 04:23:23 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir(t_token **token)
{
	t_token *tmp;

	if (!(*token))
		return (0);
	tmp = *token;
	if ((*token)->str[0] == '<' || (*token)->str[0] == '>')
	{
		if (!tmp->next)
			return (0); //bash: syntax error near unexpected token `token->str' (ou 'newline')
		if (tmp->next->token == BLANK && !tmp->next->next)
			return (0); //bash: syntax error near unexpected token `token->str' (ou 'newline')
		if (tmp->next->token == BLANK)
			tmp = tmp->next->next; 
		else
			tmp = tmp->next;
		if (tmp->token == PIPE || tmp->token == REDIR_APPEND_OUT || tmp->token == HERE_DOC || tmp->token == REDIR_IN || tmp->token == REDIR_OUT)
		{
			return (0); //bash: syntax error near unexpected token `token->str'
		}
		tmp->token = (*token)->token;
		tmp = *token;
		*token = (*token)->next;
		t_token_del(token, tmp);
	}
	return (1);
}

static void	env(t_token **token, t_envp *menvp)
{
	t_envp	*tmp;

	if (!(*token))
		return ;
	if ((*token)->token == ENV)
	{
		tmp = t_envp_finding(menvp, (*token)->str);
		if (tmp)
		{
			free((*token)->str);
			(*token)->token = STRING;
			(*token)->str = ft_strdup(tmp->value);
		}
		else
		{
			t_token_del(token, *token);
			return ;
		}
	}
}

int	parse_tokens(t_token *token, t_envp *menvp)
{
	while (token)
	{
		env(&token, menvp);
		if (!token)
			return (0);
		if (!redir(&token))
			return (0);
		token = token->next;
	}
	return (1);
}
