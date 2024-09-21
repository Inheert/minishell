/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:58:10 by cluby             #+#    #+#             */
/*   Updated: 2024/09/21 19:52:37 by tclaereb         ###   ########.fr       */
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
		if (token)
			token = token->next;
	}
}
