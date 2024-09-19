/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:58:10 by cluby             #+#    #+#             */
/*   Updated: 2024/09/19 16:02:22 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_cmd(t_token *token)
{
	if (!token)
		return ;
	if (token->token == STRING || token->token == QUOTE)
		token->token = COMMAND;
	while (token)
	{
		if (token->token == PIPE || token->token == REDIR_APPEND_OUT || token->token == HERE_DOC || token->token == REDIR_IN || token->token == REDIR_OUT)
		{
			token = token->next;
			if (token && (token->token == STRING || token->token == QUOTE))
				token->token = COMMAND;
		}
		token = token->next;
	}
}