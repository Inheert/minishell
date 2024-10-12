/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:15:49 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/12 15:37:17 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_actual_char(char **current_str, char c)
{
	size_t	len;

	len = 0;
	if (*current_str)
		len = ft_strlen(*current_str);
	*current_str = ft_realloc(*current_str, len, len + 2);
	(*current_str)[len] = c;
	(*current_str)[len + 1] = '\0';
}

void	create_new_token(t_token **tokens, t_quote_expand_helper *helper)
{
	char	*buffer;

	if (helper->current_str && !helper->concatenate_quote)
	{
		if (helper->last_quote == 0)
		{
			buffer = ft_strtrim(helper->current_str, " \t");
			ft_free(helper->current_str);
			helper->current_str = buffer;
		}
		if (ft_strlen(helper->current_str) > 0)
			t_token_add_back(tokens, t_token_new(helper->current_str,
					STRING, helper->last_quote));
		helper->current_str = NULL;
		helper->last_quote = 0;
		helper->concatenate_quote = 1;
	}
}

t_token	*manage_last_str(t_token **tokens, t_quote_expand_helper *helper)
{
	if (helper->in_single_quote || helper->in_double_quote)
	{
		free(helper->current_str);
		return (raise_error("Parsing", "quotes unclosed.", 0, 1),
			free_t_token(*tokens), NULL);
	}
	if (helper->current_str)
		t_token_add_back(tokens, t_token_new(helper->current_str, STRING,
				helper->last_quote));
	return (*tokens);
}

void	manage_actual_word(t_quote_expand_helper *helper, t_envp *menvp)
{
	helper->j = -1;
	while (helper->word[++helper->j])
	{
		helper->c = helper->word[helper->j];
		if (manage_quotes(helper->c, &helper->in_double_quote,
				&helper->in_single_quote, &helper->last_quote))
			continue ;
		if (helper->c == ' ' && !helper->in_single_quote
			&& !helper->in_double_quote)
			helper->concatenate_quote = 0;
		if (helper->c == '$' && !helper->in_single_quote
			&& manage_env_var_expand(&helper->current_str, helper->word,
				&helper->j, menvp))
			continue ;
		concat_actual_char(&helper->current_str, helper->c);
	}
}

t_token	*process_quotes(char **lexer, t_envp *menvp)
{
	t_token					*tokens;
	t_quote_expand_helper	helper;

	tokens = NULL;
	helper.current_str = NULL;
	helper.in_single_quote = 0;
	helper.in_double_quote = 0;
	helper.last_quote = 0;
	helper.concatenate_quote = 1;
	helper.i = -1;
	while (lexer[++helper.i])
	{
		helper.word = lexer[helper.i];
		manage_actual_word(&helper, menvp);
		if (!helper.in_single_quote && !helper.in_double_quote)
			create_new_token(&tokens, &helper);
		else
			concat_actual_char(&helper.current_str, ' ');
	}
	return (manage_last_str(&tokens, &helper));
}
