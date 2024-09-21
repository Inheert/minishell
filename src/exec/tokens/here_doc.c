/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:59:24 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/20 16:35:32 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_here_doc(t_pipe *pipes, t_token *token)
{
	int		fds[2];
	char	*buff;

	if (pipe(fds) == -1)
		raise_perror("Here_doc buffer creation failed (pipe)", 1);
	if (pipes->here_doc[0] != -1 && dup2(fds[0], pipes->here_doc[0]) == -1)
		raise_perror("dup2 failed", 1);
	if (pipes->here_doc[1] != -1 && dup2(fds[1], pipes->here_doc[1]) == -1)
		raise_perror("dup2 failed", 1);
	while (1)
	{
		buff = readline("> ");
		if (buff && ft_strncmp(buff, token->str, ft_strlen(token->str)) == 0)
			break ;
		write(pipes->here_doc[1], buff, ft_strlen(buff));
		write(pipes->here_doc[1], "\n", 1);
	}
	if (pipes->here_doc[0] != -1 && dup2(pipes->here_doc[0], 0) == -1)
		return (t_pipe_close_fds(pipes), raise_perror("dup2 failed", 1), NULL);
	return (token);
}
