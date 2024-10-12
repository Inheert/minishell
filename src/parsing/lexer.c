/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:57:21 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/10/11 17:49:30 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Creat a table, the result for function lexer_split.
 */
char	**create_the_table(char **result, const char *line)
{
	t_help	h;

	h.count = 0;
	h.start = 0;
	h.i = 0;
	while (line[h.i])
	{
		if (handle_quotes_table(result, line, &h, '\''))
			continue ;
		if (handle_quotes_table(result, line, &h, '"'))
			continue ;
		if (handle_specials_or_spaces_table(result, line, &h))
			continue ;
		h.i++;
	}
	if ((int)h.i > h.start)
		result[h.count++] = ft_substr(line, h.start, h.i - h.start);
	result[h.count] = NULL;
	return (result);
}

int	lexer_test_quotes(const char *line)
{
	int		single_quote;
	int		double_quote;
	int		i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && double_quote == 0)
			single_quote ^= 1;
		if (line[i] == '\"' && single_quote == 0)
			double_quote ^= 1;
		i++;
	}
	if (double_quote == 1 || single_quote == 1)
		return (raise_error("Parsing", "unclosed quote.", 0, 1), 0);
	return (1);
}

char	**lexer_split(const char *line, int i)
{
	char	**result;
	t_help	h;

	h.count = 0;
	h.start = 0;
	result = NULL;
	if (!lexer_test_quotes(line))
		return (NULL);
	while (line[i])
	{
		if (handle_quotes(line, &i, &h, '\''))
			continue ;
		if (handle_quotes(line, &i, &h, '\"'))
			continue ;
		if (handle_specials_or_spaces(line, &i, &h))
			continue ;
		i++;
	}
	if (i > h.start)
		h.count++;
	result = ft_malloc(sizeof(char *) * (h.count + 1));
	return (create_the_table(result, line));
}

/**
 * Splite the prompt from char * into char **
 * - puts every space in a char *
 * - the quotes and what is inside into a char *
 *
 * */
char	**manage_lexer(const char *line)
{
	char		**lexer;
	int			i;

	i = 0;
	lexer = lexer_split(line, i);
	if (!lexer)
		return (NULL);
	return (lexer);
}
