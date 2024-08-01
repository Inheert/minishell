/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:59:31 by cluby             #+#    #+#             */
/*   Updated: 2024/07/29 19:44:07 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_tokens(t_token *token)
{
	while (token)
	{
		if (token->token = ENV)
		{
			token->token = EXIT_STATUS;
		}
		if (token->str[0] == NULL)
		{
			if (token->prev)
				token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			free(token->str);
			free(token);
		}
	}
}