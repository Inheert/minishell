/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:59:46 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/10 17:06:50 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_redir_in(t_pipe *pipes, t_token *token, int *fdin)
{
	*fdin = open(token->str, O_RDONLY);
	if (*fdin == -1)
		return (t_pipe_close_fds(pipes),
			raise_perror(token->str, 1), NULL);
	return (token);
}

t_token	*ft_redir_out(t_pipe *pipes, t_token *token, int *fdout)
{
	fprintf(stderr, "%d\n", token->token == REDIR_APPEND_OUT);
	if (token->token == REDIR_OUT)
		*fdout = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*fdout = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fdout == -1)
		return (t_pipe_close_fds(pipes),
			raise_perror(token->str, 1), NULL);
	return (token);
}

void	ft_check_redir_in_out(t_pipe *pipes, int fdin, int fdout)
{
	if (fdin != -1)
	{
		if (dup2(fdin, 0) == -1)
			return (t_pipe_close_fds(pipes),
				raise_perror("dup2 failed", 1));
		pipes->fds[0] = fdin;
	}
	if (fdout != -1)
	{
		if (dup2(fdout, 1) == -1)
			return (t_pipe_close_fds(pipes),
				raise_perror("dup2 failed", 1));
		pipes->fds[1] = fdout;
	}
}
