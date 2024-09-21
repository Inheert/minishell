/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:53:11 by cluby             #+#    #+#             */
/*   Updated: 2024/09/20 13:19:35 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_quote(t_token *token, char *prompt, int *i)
{
	int j;

	j = 0;
	if (prompt[*i] == '\'')
	{
		*i += 1;
		j = *i;
		while(prompt[*i] != '\0' && prompt[*i] != '\'')
		{
			*i += 1;		
		}
		printf("j = %d\n i = %d\n", j, *i);
		if (token)
			t_token_add_back(&token, \
			t_token_new(ft_substr(prompt, j, *i - j), QUOTE));
		else
			token = t_token_new(ft_substr(prompt, j, *i - j), QUOTE);
		printf("char prompt = %c\n", prompt[*i]);
		i += 1;
	}
}

void	blanks(t_token *token, char *prompt, int *i)
{
	int j;

	j = 0;
	if (prompt[*i] == ' ' || prompt[*i] == '\t')
	{
		j = *i;
		*i += 1;
		while (prompt[*i] == ' ' || prompt[*i] == '\t')
			i++;
		if (token)
			t_token_add_back(&token, \
			t_token_new(ft_substr(prompt, j, *i - j), BLANK));
		else
			token = t_token_new(ft_substr(prompt, j, *i - j), BLANK);
	}
}
