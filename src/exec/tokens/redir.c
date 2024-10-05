/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:59:46 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/05 17:58:43 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_redir_in(t_processus *pipes, t_token *token, int *fdin)
{
	if (*fdin != -1)
		close(*fdin);
	*fdin = open(token->str, O_RDONLY);
	if (*fdin == -1)
	{
		if (pipes->parent_pid == getpid())
			return (t_processus_close_fds(pipes),
				raise_perror(token->str, 1), NULL);
		else
			return (t_processus_close_fds(pipes),
				raise_perror(token->str, 1), NULL);
	}
	return (token);
}

t_token	*ft_redir_out(t_processus *pipes, t_token *token, int *fdout)
{
	if (*fdout != -1)
		close(*fdout);
	if (token->token == REDIR_OUT)
		*fdout = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token->token == REDIR_APPEND_OUT)
		*fdout = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fdout == -1)
	{
		if (pipes->parent_pid == getpid())
			return (t_processus_close_fds(pipes),
				raise_perror(token->str, 1), NULL);
		else
			return (t_processus_close_fds(pipes),
				raise_perror(token->str, 1), NULL);
	}
	return (token);
}

static int	is_heredoc_a_priority(t_processus *pipes, int fdin, int fdout)
{
	t_token	*here_doc;
	t_token	*tmp;

	here_doc = t_token_finding(pipes, HERE_DOC);
	if (!here_doc)
		return (0);
	tmp = here_doc;
	while (tmp)
	{
		if (tmp->token == REDIR_IN)
			return (0);
		tmp = tmp->next;
	}
	if (fdin != -1)
		close(fdin);
	if (fdout != -1)
		close(fdout);
	if (dup2(pipes->here_doc[0], 0) == -1)
		return (t_processus_close_fds(pipes),
			raise_perror("dup2 failed", 1), 1);
	return (1);
}

void	ft_check_redir_in_out(t_processus *pipes, int fdin, int fdout)
{
	if (!is_heredoc_a_priority(pipes, fdin, fdout) && fdin != -1)
	{
		if (dup2(fdin, 0) == -1)
			return (t_processus_close_fds(pipes),
				raise_perror("dup2 failed", 1));
		if (pipes->fds[0] != -1)
			close(pipes->fds[0]);
		pipes->fds[0] = fdin;
	}
	if (fdout != -1)
	{
		if (dup2(fdout, 1) == -1)
			return (t_processus_close_fds(pipes),
				raise_perror("dup2 failed", 1));
		if (pipes->fds[1] != -1)
			close(pipes->fds[1]);
		pipes->fds[1] = fdout;
	}
}
