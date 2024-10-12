/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:23:29 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/10/12 15:01:28 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_after_red(t_token *token, int *after_red)
{
	if (token)
	{
		token = token->next;
		if (!token)
			return (*after_red = -1);
		else if (ft_strncmp(token->str, "|", 1) == 0
			&& token->str[0] != '<' && token->str[0] != '>')
			return (*after_red = -1);
		else if (ft_strncmp(token->str, "|", 1) == 0)
			return (*after_red = -1);
		else if (ft_strncmp(token->str, ">", 1) == 0)
			return (*after_red = -1);
		else if (ft_strncmp(token->str, "<", 1) == 0)
			return (*after_red = -1);
		else if (token->str[0] == '&')
			return (*after_red = -1);
		else
			return (*after_red = 1);
	}
	return (1);
}

/**
 * find the token type
 * PROBLEMA
 * - cuando after_red es 1 y le sigue un pipe o redireccion
 *
 */
t_token_type	find_type(t_token *tmp, int *after_red)
{
	if (*after_red == 1)
		return (*after_red = 0, FILLE);
	else if (tmp->flag_quotes != 0)
		return (STRING);
	else if (ft_strncmp(tmp->str, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(tmp->str, ">>", 2) == 0)
		return (*after_red = change_after_red(tmp, after_red),
			REDIR_APPEND_OUT);
	else if (ft_strncmp(tmp->str, "<<", 2) == 0)
		return (*after_red = change_after_red(tmp, after_red), HEREDOC);
	else if (ft_strncmp(tmp->str, ">", 1) == 0)
		return (*after_red = change_after_red(tmp, after_red), REDIR_OUT);
	else if (ft_strncmp(tmp->str, "<", 1) == 0)
		return (*after_red = change_after_red(tmp, after_red), REDIR_IN);
	return (STRING);
}

int	look_for_dol(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	find_type_command(t_token *tmp, t_token *tokens)
{
	tmp = t_token_finding(tokens, STRING);
	while (tmp)
	{
		if (tmp)
			tmp->token = COMMAND;
		tmp = t_token_finding(tmp, PIPE);
		if (!tmp)
			break ;
		tmp = t_token_finding(tmp, STRING);
	}
}

/**
 * Return noting just modiffy the token type inthe node
 */
int	find_token_type(t_token **tokens, t_envp *menvp)
{
	t_token	*tmp;
	int		after_red;
	t_token	*buff;

	(void)menvp;
	after_red = 0;
	buff = NULL;
	tmp = *tokens;
	while (tmp && tmp->str)
	{
		tmp->token = find_type(tmp, &after_red);
		if (after_red == -1)
			return (after_red);
		if (tmp->str == NULL)
			buff = tmp;
		tmp = tmp->next;
		t_token_del(tokens, buff);
	}
	find_type_command(tmp, *tokens);
	return (after_red);
}
