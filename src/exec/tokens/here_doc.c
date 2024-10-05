/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:59:24 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/05 23:27:34 by Théo             ###   ########.fr       */
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
		//free(buff);
	}
	return (token);
}

void	ft_here_docs(t_processus *pipes)
{
	t_token	*here_doc;

	while (pipes)
	{
		here_doc = t_token_finding(pipes, HERE_DOC);
		while (here_doc)
		{
			if (here_doc->token == HERE_DOC)
				manage_here_doc(pipes, here_doc);
			here_doc = here_doc->next;
		}
		pipes = pipes->next;
	}
}
