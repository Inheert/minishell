/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:02:15 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/10/10 12:15:08 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * handle the quotes in the table lexer
 */
int	handle_quotes_table(char **result, const char *line,
				t_help *h, char quote_char)
{
	int	inside_quote;

	inside_quote = 0;
	if (line[h->i] == quote_char)
	{
		inside_quote ^= 1;
		if (inside_quote == 1)
		{
			if ((int)h->i > h->start)
				result[(h->count)++] = ft_substr(line, h->start,
						h->i - h->start);
			h->start = h->i;
			(h->i)++;
			while (line[h->i] != quote_char)
				(h->i)++;
			result[(h->count)++] = ft_substr(line, h->start,
					h->i - h->start + 1);
			h->start = h->i + 1;
			(h->i)++;
			return (1);
		}
	}
	return (0);
}

/**
 * 
 * Handle for the creation of the table of char like <, >, |, $
 */
int	handle_specials_or_spaces_table(char **result, const char *line, t_help *h)
{
	if (line[h->i] == ' ' || line[h->i] == '<'
		|| line[h->i] == '>' || line[h->i] == '|')
	{
		if ((int)h->i > h->start)
			result[(h->count)++] = ft_substr(line, h->start, h->i - h->start);
		h->start = h->i;
		if (line[h->i] == ' ')
			while (line[h->i] == ' ')
				(h->i)++;
		else
		{
			if (line[h->i] != '|')
			{
				(h->i)++;
				if (line[h->i] == '<' || line[h->i] == '>')
					(h->i)++;
			}
			else
				(h->i)++;
		}
		result[(h->count)++] = ft_substr(line, h->start, h->i - h->start);
		h->start = h->i;
		return (1);
	}
	return (0);
}

/**
 * handle the quotes alocation for the lexer
 */
int	handle_quotes(const char *line, int *i, t_help *h, char quote_char)
{
	if (line[*i] == quote_char)
	{
		h->count += (*i > h->start);
		h->start = *i;
		(*i)++;
		while (line[*i] && line[*i] != quote_char)
			(*i)++;
		(*i)++;
		h->count += 1;
		h->start = *i;
		return (1);
	}
	return (0);
}

/**
 * handle for the allocation of char like <, >, |, $
 */
int	handle_specials_or_spaces(const char *line, int *i, t_help *h)
{
	if (line[*i] == ' ' || line[*i] == '<' || line[*i] == '>'
		|| line[*i] == '|' || line[*i] == '$')
	{
		h->count += (*i > h->start);
		h->start = *i;
		if (line[*i] == ' ')
			while (line[*i] && line[*i] == ' ')
				(*i)++;
		else
		{
			if (line[*i] != '|')
			{
				(*i)++;
				if (line[*i] == '<' || line[*i] == '>')
					(*i)++;
			}
			else
				(*i)++;
		}
		h->start = *i;
		h->count += 1;
		return (1);
	}
	return (0);
}
