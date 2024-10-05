/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:59:46 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/06 01:18:35 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_redir_in(t_processus *process, t_token *token, int *fdin)
{
	if (*fdin != -1)
		close(*fdin);
	*fdin = open(token->str, O_RDONLY);
	if (*fdin == -1)
	{
		if (process->parent_pid == getpid())
			return (t_processus_close_fds(process),
				raise_perror(token->str, 0), NULL);
		else
			return (t_processus_close_fds(process),
				raise_perror(token->str, 1), NULL);
	}
	return (token);
}

t_token	*ft_redir_out(t_processus *process, t_token *token, int *fdout)
{
	if (*fdout != -1)
		close(*fdout);
	if (token->token == REDIR_OUT)
		*fdout = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token->token == REDIR_APPEND_OUT)
		*fdout = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fdout == -1)
	{
		if (process->parent_pid == getpid())
			return (t_processus_close_fds(process),
				raise_perror(token->str, 0), NULL);
		else
			return (t_processus_close_fds(process),
				raise_perror(token->str, 1), NULL);
	}
	return (token);
}

static int	is_heredoc_a_priority(t_processus *process, int fdin)
{
	t_token	*here_doc;
	t_token	*tmp;
	int		is_redir_after_here_doc;

	is_redir_after_here_doc = 0;
	here_doc = t_token_finding(process, HERE_DOC);
	if (!here_doc)
		return (0);
	tmp = here_doc;
	while (tmp)
	{
		if (tmp->token == REDIR_IN)
			is_redir_after_here_doc = 1;
		else if (tmp->token == HERE_DOC)
			is_redir_after_here_doc = 0;
		tmp = tmp->next;
	}
	if (is_redir_after_here_doc)
		return (0);
	if (fdin != -1)
		close(fdin);
	if (dup2(process->here_doc[0], 0) == -1)
		return (t_processus_close_fds(process),
			raise_perror("dup2 failed", 1), 1);
	return (1);
}

static void	close_here_docs(t_processus *process)
{
	if (process->here_doc[0] > 0)
		close(process->here_doc[0]);
	if (process->here_doc[1] > 1)
		close(process->here_doc[1]);
	process->here_doc[0] = -1;
	process->here_doc[1] = -1;
}

void	ft_check_redir_in_out(t_processus *process, int fdin, int fdout)
{
	int	get_heredoc_as_input;

	get_heredoc_as_input = is_heredoc_a_priority(process, fdin);
	if (!get_heredoc_as_input && fdin != -1)
	{
		if (dup2(fdin, 0) == -1)
			return (t_processus_close_fds(process),
				raise_perror("dup2 failed", 1));
		if (process->fds[0] > 0)
			close(process->fds[0]);
		process->fds[0] = fdin;
	}
	if (!get_heredoc_as_input)
		close_here_docs(process);
	if (fdout != -1)
	{
		if (dup2(fdout, 1) == -1)
			return (t_processus_close_fds(process),
				raise_perror("dup2 failed", 1));
		if (process->fds[1] > 1)
			close(process->fds[1]);
		process->fds[1] = fdout;
	}
}
