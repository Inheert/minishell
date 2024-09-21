/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:49:29 by cluby             #+#    #+#             */
/*   Updated: 2024/09/20 13:23:38 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_env(t_token *token)
{
	char	**tmp;
	int		i;
	t_token	*tmp_token;

	tmp = ft_split(token->str, '$');
	if (!tmp)
		return ; //error
	i = 0;
	tmp_token = token;
	free(token->str);
	tmp_token->str = ft_strdup(tmp[i]);
	i++;
	while (tmp[i])
	{
		t_token_add_back(&token, t_token_new(ft_strdup(tmp[i]), ENV));
		i++;
	}
	return ;
}

t_token *tokenisation(char *prompt)
{
	int	i;
	int	j;
	t_token	*token;

	token = NULL;
	i = 0;
	j = 0;
	while (prompt[i] != '\0')
	{
		if (prompt[i] == ' ' || prompt[i] == '\t')
		{
			j = i;
			i++;
			while (prompt[i] == ' ' || prompt[i] == '\t')
				i++;
			if (token)
				t_token_add_back(&token, t_token_new(ft_substr(prompt, j, i - j), BLANK));
			else
				token = t_token_new(ft_substr(prompt, j, i - j), BLANK);
		}
		if (prompt[i] == '\'')
		{
			i++;
			j = i;
			while(prompt[i] != '\0' && prompt[i] != '\'')
				i++;
			// printf("i = %d\nj = %d\n", i, j);
			if (token)
				t_token_add_back(&token, t_token_new(ft_substr(prompt, j, i - j), QUOTE));
			else
				token = t_token_new(ft_substr(prompt, j, i - j), QUOTE);
			i++;
		}
		blanks(token, prompt, &i);
		simple_quote(token, prompt, &i);
		if (prompt[i] == '"')
		{
			i++;
			if (prompt[i] == '"')
			{
				if (token)
					t_token_add_back(&token, t_token_new("", QUOTE));
				else
					token = t_token_new("", QUOTE);
				i++;
			}
			while(prompt[i] != '\0' && prompt[i] != '"' )
			{
				j = i;
				while (prompt[i] != '$' && prompt[i] != '\0' && prompt[i] != '\"')
					i++;
				// printf("i = %d\nj = %d\n", i, j);
				if (token)
				{
					if (i == j)
						t_token_add_back(&token, t_token_new("", QUOTE));
					t_token_add_back(&token, t_token_new(ft_substr(prompt, j, i - j), QUOTE));	
				}
				else
				{
					if (i == j)
						token = t_token_new("", QUOTE);
					token = t_token_new(ft_substr(prompt, j, i - j), QUOTE);
				}
				if (prompt[i] == '$')
				{
					i++;
					j = i;
					while(prompt[i] != '\0' && prompt[i] != ' ' && prompt[i] != '\t' && prompt[i] != '\"' && prompt[i] != '\'')
						i++;
					if (token)
						t_token_add_back(&token, t_token_new(ft_substr(prompt, j, i - j), ENV));
					else
						token = t_token_new(ft_substr(prompt, j, i - j), ENV);
					split_env(t_token_last(token));
				}
			}
			i++;
		}
		if (prompt[i] == '|')
		{
			if (token)
				t_token_add_back(&token, t_token_new("|", PIPE));
			else
				token = t_token_new("|", PIPE);
			i++;
		}
		if (prompt[i] == '<')
		{
			if (prompt[i + 1] && prompt[i + 1] == '<')
			{
				if (token)
					t_token_add_back(&token, t_token_new("<<", HERE_DOC));
				else
					token = t_token_new("<<", HERE_DOC);
				i++;
			}
			else
			{
				if (token)
					t_token_add_back(&token, t_token_new("<", REDIR_IN));
				else
					token = t_token_new("<", REDIR_IN);
			}
			i++;
		}
		if (prompt[i] == '>')
		{
			if (prompt[i + 1] && prompt[i + 1] == '>')
			{
				if (token)
					t_token_add_back(&token, t_token_new(">>", REDIR_APPEND_OUT));
				else
					token = t_token_new(">>", REDIR_APPEND_OUT);
				i++;
			}
			else
			{
				if (token)
					t_token_add_back(&token, t_token_new(">", REDIR_OUT));
				else
					token = t_token_new(">", REDIR_OUT);
			}
			i++;
		}
		if (prompt[i] == '$')
		{
			i++;
			j = i;
			while(prompt[i] != '\0' && prompt[i] != ' ' && prompt[i] != '\t' && prompt[i] != '\"' && prompt[i] != '\'')
				i++;
			if (token)
				t_token_add_back(&token, t_token_new(ft_substr(prompt, j, i - j), ENV));
			else
				token = t_token_new(ft_substr(prompt, j, i - j), ENV);
			split_env(t_token_last(token));
		}
		j = i;
		while (prompt[i] != '\0' && prompt[i] != '<' && prompt[i] != '>' && prompt[i] != '|' && prompt[i] != '\'' && prompt[i] != '"' && prompt[i] != '$' && prompt[i] != ' ' && prompt[i] != '\t')
		{
			i++;
		}
		if (token && i != j)
			t_token_add_back(&token, t_token_new(ft_substr(prompt, j, i - j), STRING));
		else if (i != j)
			token = t_token_new(ft_substr(prompt, j, i - j), STRING);
	}
	return (token);
}
