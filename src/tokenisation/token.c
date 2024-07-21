/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:49:29 by cluby             #+#    #+#             */
/*   Updated: 2024/07/12 17:14:41 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			j = i;
			while(ft_isascii(prompt[i]) && prompt[i] != '\0' && prompt[i] != '"' && prompt[i] != '$')
				i++;
			if (prompt[i] == '\0')
				return (NULL);
			if (token)
				ft_token_add_back(&token, ft_token_new(ft_substr(prompt, j, i - j), STRING));
			else
				token = ft_token_new(ft_substr(prompt, j, i - j), STRING);
			if (prompt[i] == '$')
			{
				i++;
				j = i;
				while(ft_isascii(prompt[i]) && prompt[i] != '\0' && prompt[i] != ' ' && prompt[i] != '\t' && prompt[i] != '"' && prompt[i] != '\'' && prompt[i] != '$')
					i++;
				if (token)
					ft_token_add_back(&token, ft_token_new(ft_substr(prompt, j, i - j), ENV));
				else
					token = ft_token_new(ft_substr(prompt, j, i - j), ENV);
			}
			//new token STRING_VAR
			//add token if needed		
		}
		/* if (argv[i] == '|')
		{
			//new token PIPE
			//add token if needed
			i++;
		} */
		i++;
	}
	return (token);
}
