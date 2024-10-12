/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:08:56 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/10/12 15:36:40 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_quotes(char c, int *in_double_quote, int *in_single_quote,
	int *last_quote)
{
	if (c == '\'' && !*in_double_quote)
	{
		*in_single_quote = !*in_single_quote;
		*last_quote = 1;
		return (1);
	}
	if (c == '\"' && !*in_single_quote)
	{
		*in_double_quote = !*in_double_quote;
		*last_quote = 2;
		return (1);
	}
	return (0);
}

int	manage_env_var_expand(char **current_str, char *word, int *j,
	t_envp *menvp)
{
	t_envp	*env_value;
	char	*env_var;
	int		k;
	size_t	len;

	k = *j + 1;
	while (word[k] && (ft_isalnum(word[k]) || word[k] == '_'))
		k++;
	env_var = ft_substr(word, *j + 1, k - *j - 1);
	env_value = t_envp_finding(menvp, env_var);
	if (env_value)
	{
		if (*current_str)
		{
			len = ft_strlen(*current_str);
			*current_str = ft_realloc(*current_str, len,
					len + ft_strlen(env_value->value) + 1);
			strcat(*current_str, env_value->value);
		}
		else
			*current_str = ft_strdup(env_value->value);
	}
	*j = k - 1;
	ft_free(env_var);
	return (1);
}

/**
 * Eliminate the redir of the tokens list
 * kiping the flag_quotes and the str.
 */
int	concat_token_redir(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->next && tmp->token >= 1 && tmp->token <= 4
			&& tmp->next->token >= 1 && tmp->next->token <= 4)
			return (0);
		else if (tmp->next && tmp->token >= 1 && tmp->token <= 4)
		{
			ft_free(tmp->str);
			tmp->str = ft_strdup(tmp->next->str);
			tmp->flag_quotes = tmp->next->flag_quotes;
			t_token_del(tokens, tmp->next);
		}
		else if (!tmp->next && tmp->token >= 1 && tmp->token <= 4)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
