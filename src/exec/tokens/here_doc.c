/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:59:24 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/05 17:55:52 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*manage_here_doc(t_processus *pipes, t_token *token)
{
	char	*buff;

	if (pipes->here_doc[0] != -1)
		close(pipes->here_doc[0]);
	if (pipes->here_doc[1] != -1)
		close(pipes->here_doc[1]);
	if (pipe(pipes->here_doc) == -1)
		raise_perror("Here_doc buffer creation failed (pipe)", 1);
	while (1)
	{
		buff = readline("> ");
		if (buff && ft_strcmp(buff, token->str) == 0)
			break ;
		write(pipes->here_doc[1], buff, ft_strlen(buff));
		write(pipes->here_doc[1], "\n", 1);
	}
	return (token);
}

void	ft_here_docs(t_processus *pipes)
{
	t_token	*here_doc;

	while (pipes)
	{
		here_doc = t_token_finding(pipes, HERE_DOC);
		if (here_doc)
			manage_here_doc(pipes, here_doc);
		pipes = pipes->next;
	}
}
