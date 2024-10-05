/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:58:10 by cluby             #+#    #+#             */
/*   Updated: 2024/10/06 01:30:01 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_cmd(t_token **tokens)
{
	t_token *tmp;

	tmp = (*tokens);
	if (!tmp)
		return ;
	if (tmp->token == STRING || tmp->token == QUOTE)
		tmp->token = COMMAND;
	while (tmp)
	{
		if (tmp->token == PIPE || tmp->token == REDIR_APPEND_OUT || tmp->token == HEREDOC || tmp->token == REDIR_IN || tmp->token == REDIR_OUT)
		{
			tmp = tmp->next;
			if (tmp->token == BLANK && tmp)
				tmp = tmp->next;
			if (tmp && (tmp->token == STRING || tmp->token == QUOTE))
				tmp->token = COMMAND;
		}
		if (tmp)
			tmp = tmp->next;
	}
}
