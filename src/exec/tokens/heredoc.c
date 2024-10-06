/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:59:24 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/06 01:24:44 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function reproduce the bash heredoc.
static t_token	*manage_heredoc(t_processus *process, t_token *token)
{
	char	*buff;

	if (process->heredoc[0] != -1)
		close(process->heredoc[0]);
	if (process->heredoc[1] != -1)
		close(process->heredoc[1]);
	if (pipe(process->heredoc) == -1)
		raise_perror("heredoc buffer creation failed (pipe)", 1);
	while (1)
	{
		buff = readline("> ");
		if (buff && ft_strcmp(buff, token->str) == 0)
			break ;
		write(process->heredoc[1], buff, ft_strlen(buff));
		write(process->heredoc[1], "\n", 1);
		free(buff);
	}
	free(buff);
	return (token);
}

void	ft_heredocs(t_processus *process)
{
	t_token	*heredoc;

	while (process)
	{
		heredoc = t_token_finding(process, HEREDOC);
		while (heredoc)
		{
			if (heredoc->token == HEREDOC)
				manage_heredoc(process, heredoc);
			heredoc = heredoc->next;
		}
		process = process->next;
	}
}
