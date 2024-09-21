/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:54:22 by cluby             #+#    #+#             */
/*   Updated: 2024/09/21 19:49:57 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_tokens(t_token *token)
{
	while (token)
	{
		if (token->token == STRING || token->token == QUOTE)
		{
			while (token->next && (token->next->token == STRING || token->next->token == QUOTE))
			{
				token->str = ft_strjoin(token->str, token->next->str);
				t_token_del(&token, token->next);
			}
		}
		token = token->next;
	}
}
