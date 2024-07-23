/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:49:29 by cluby             #+#    #+#             */
/*   Updated: 2024/07/19 15:48:07 by cluby            ###   ########.fr       */
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
		ft_token_add_back(&token, ft_token_new(ft_strdup(tmp[i]), ENV));
		i++;
	}
	return ;
}

t_token *tokenization(char *prompt)
{
	int	i;
	int	j;
	t_token	*token;

	token = NULL;
	i = 0;
	j = 0;
	while (prompt[i] != '\0')
	{
		while (prompt[i] == ' ' || prompt[i] == '\t')
			i++;
		if (prompt[i] == '\'')
		{
			i++;
			//check quote number
			//delete quotes if even number
			j = i;
			while(ft_isascii(prompt[i]) && prompt[i] != '\0' && prompt[i] != '\'')
				i++;
			if (prompt[i] == '\0')
				return (NULL); //error
			if (token)
				ft_token_add_back(&token, ft_token_new(ft_substr(prompt, j, i - j), STRING));
			else
				token = ft_token_new(ft_substr(prompt, j, i - j), STRING);
		}
		if (prompt[i] == '"')
		{
			i++;
			//check quote number
			//delete quotes if even number
			while(ft_isascii(prompt[i]) && prompt[i] != '\0' && prompt[i] != '"' )
			{
				j = i;
				while (prompt[i] != '$' && prompt[i] != '\0' && prompt[i] != '\"')
					i++;
				if (token)
					ft_token_add_back(&token, ft_token_new(ft_substr(prompt, j, i - j), STRING));
				else
					token = ft_token_new(ft_substr(prompt, j, i - j), STRING);
				if (prompt[i] == '$')
				{
					i++;
					j = i;
					while(ft_isascii(prompt[i]) && prompt[i] != '\0' && prompt[i] != ' ' && prompt[i] != '\t' && prompt[i] != '\"' && prompt[i] != '\'')
						i++;
					if (token)
						ft_token_add_back(&token, ft_token_new(ft_substr(prompt, j, i - j), ENV));
					else
						token = ft_token_new(ft_substr(prompt, j, i - j), ENV);
					split_env(last_token(token));
				}	
			}
			if (prompt[i] == '\0')
				return (NULL);
		}
		if (prompt[i] == '|')
		{
			if (token)
				ft_token_add_back(&token, ft_token_new("|", PIPE));
			else
				token = ft_token_new("|", PIPE);
			i++;
		}
		i++;
	}
	return (token);
}
