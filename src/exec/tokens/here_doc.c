/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:59:24 by tclaereb          #+#    #+#             */
/*   Updated: 2024/08/24 17:03:17 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_here_doc(t_pipe *pipes, t_token *token)
{
	char	*buff;

	if (pipes->here_doc[0] == -1 && pipes->here_doc[1] == -1)
	if (pipe(pipes->here_doc) == -1)
		raise_perror("Here_doc buffer creation failed (pipe)", 1);
	while (1)
	{
		buff = readline("> ");
		if (buff && ft_strncmp(buff, token->str, ft_strlen(token->str)) == 0)
			break ;
		write(pipes->here_doc[1], buff, ft_strlen(buff));
		write(pipes->here_doc[1], "\n", 1);
	}
	if (dup2(pipes->here_doc[0], 0) == -1)
		return (ft_pipe_close_fds(pipes), raise_perror("dup2 failed", 1), NULL);
	return (token);
}