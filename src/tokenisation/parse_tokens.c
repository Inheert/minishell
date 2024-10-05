/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:59:31 by cluby             #+#    #+#             */
/*   Updated: 2024/10/06 01:29:52 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir(t_token *token, t_token **token_origin)
{
	t_token *tmp;

	if (!token)
		return (0);
	tmp = token;
	if (token->str[0] == '<' || token->str[0] == '>')
	{
		if (!tmp->next)
			return (0); //bash: syntax error near unexpected token `token->str' (ou 'newline')
		if (tmp->next->token == BLANK && !tmp->next->next)
			return (0); //bash: syntax error near unexpected token `token->str' (ou 'newline')
		if (tmp->next->token == BLANK)
			tmp = tmp->next->next;
		else
			tmp = tmp->next;
		if (tmp->token == PIPE || tmp->token == REDIR_APPEND_OUT || tmp->token == HEREDOC || tmp->token == REDIR_IN || tmp->token == REDIR_OUT)
		{
			return (0); //bash: syntax error near unexpected token `token->str'
		}
		tmp->token = token->token;
		// printf("TOKEN %d %s, next: %p\n", tmp->token, tmp->str, tmp->next);
		t_token_del(token_origin, token);
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

int	parse_tokens(t_token **token, t_envp *menvp)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		env(token, menvp);
		if (!*token)
			return (0);
		if (!redir(tmp, token))
			return (0);
		if (!tmp)
			return (1);
		tmp = tmp->next;
	}
	return (1);
}
