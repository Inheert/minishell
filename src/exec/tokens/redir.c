/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:59:46 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/06 18:34:39 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*manage_redir_in(t_processus *process, t_token *token, int *fdin)
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

t_token	*manage_redir_out(t_processus *process, t_token *token, int *fdout)
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

// Used to know if the heredoc is the last redir in token in the current
// command line, if yes then it dup2 the standard entry and avoid future dup2,
// else it close heredoc fds and let the program dup2 other infile.
static int	is_heredoc_a_priority(t_processus *process, int fdin)
{
	t_token	*heredoc;
	t_token	*tmp;
	int		is_redir_after_heredoc;

	heredoc = t_token_finding(process, HEREDOC);
	if (!heredoc)
		return (0);
	is_redir_after_heredoc = 0;
	tmp = heredoc;
	while (tmp)
	{
		if (tmp->token == REDIR_IN)
			is_redir_after_heredoc = 1;
		else if (tmp->token == HEREDOC)
			is_redir_after_heredoc = 0;
		tmp = tmp->next;
	}
	if (is_redir_after_heredoc)
		return (0);
	if (fdin != -1)
		close(fdin);
	if (dup2(process->heredoc[0], 0) == -1)
		return (t_processus_close_fds(process),
			raise_perror("dup2 failed", 1), 1);
	return (1);
}

// Used to close heredocs fds.
static void	close_heredocs(t_processus *process)
{
	if (process->heredoc[0] > 0)
		close(process->heredoc[0]);
	if (process->heredoc[1] > 1)
		close(process->heredoc[1]);
	process->heredoc[0] = -1;
	process->heredoc[1] = -1;
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
		close_heredocs(process);
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
