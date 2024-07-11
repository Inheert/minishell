/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:49:29 by cluby             #+#    #+#             */
/*   Updated: 2024/07/11 18:01:27 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token tokenization(t_token *token, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '|')
			token->token = PIPE;
		else if (argv[i] == ';')
			token->token = SEMICOLON;
		else if (argv[i] == '>')
			token->token = REDIR_OUT;
		else if (argv[i] == '<')
			token->token = REDIR_IN;
		else if (argv[i] == '>>')
			token->token = REDIR_APPEND;
		
		i++;
	}
}
