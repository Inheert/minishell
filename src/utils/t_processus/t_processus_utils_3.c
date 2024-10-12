/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_processus_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:58:29 by Théo              #+#    #+#             */
/*   Updated: 2024/10/11 19:15:25 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_potential_fd_to_count(t_token *tokens, t_token_type type)
{
	tokens = t_token_finding(tokens, type);
	if (tokens)
		return (0);
	return (1);
}

int	does_fds_count_exceed_the_limit(t_processus *process)
{
	int		count;

	count = 0;
	while (process)
	{
		count += add_potential_fd_to_count(process->tokens, REDIR_IN);
		count += add_potential_fd_to_count(process->tokens, REDIR_OUT);
		count += add_potential_fd_to_count(process->tokens, REDIR_APPEND_OUT);
		count += add_potential_fd_to_count(process->tokens, HEREDOC);
		if (process->next)
			count += 2;
		if (count > 1024)
			return (1);
		process = process->next;
	}
	if (count > 1024)
		return (1);
	return (0);
}
