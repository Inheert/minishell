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

static void	prepare_heredoc_error(char *delimiter)
{
	if (g_signal_code == SIGINT)
	{
		g_signal_code = 0;
		set_exit_status(130, NULL);
	}
	else
	{
		ft_putstr_fd("\nwarning: here-document delimited", 1);
		ft_putstr_fd("by end-of-file (wanted '", 1);
		ft_putstr_fd(delimiter, 1);
		ft_putstr_fd("')\n", 1);
		raise_error(NULL, NULL, 0, 0);
	}
}

static void	expand_heredoc(char *line, t_token *token, t_processus *process)
{
	t_token	*new_line_token;
	char	**line_storage;

	if (token->flag_quotes != 0 || !ft_strchr(line, '$'))
	{
		write(process->heredoc[1], line, ft_strlen(line));
		write(process->heredoc[1], "\n", 1);
	}
	else
	{
		line_storage = ft_malloc(sizeof(char *) * 2);
		line_storage[0] = line;
		line_storage[1] = NULL;
		new_line_token = process_quotes(line_storage, *process->menvp);
		if (new_line_token)
			write(process->heredoc[1], new_line_token->str,
					ft_strlen(new_line_token->str));
		write(process->heredoc[1], "\n", 1);
		free_t_token(new_line_token);
		free_str_ptr(line_storage);
	}
	ft_free(line);
}

static void	heredoc_core(t_processus *process, t_token *token,
	char *tmp, char *buff)
{
	while (1)
	{
		ft_putstr_fd(">", 1);
		buff = get_next_line(STDOUT_FILENO);
		tmp = buff;
		buff = ft_strtrim(buff, "\n");
		ft_free(tmp);
		if (g_signal_code == SIGQUIT)
			buff = get_next_line(STDOUT_FILENO);
		if (!buff || g_signal_code == SIGINT)
		{
			prepare_heredoc_error(token->str);
			break ;
		}
		if (buff && ft_strcmp(buff, token->str) == 0)
			break ;
		expand_heredoc(buff, token, process);
	}
	ft_free(buff);
}

// This function reproduce the bash heredoc.
static t_token	*ft_heredoc(t_processus *process, t_token *token)
{
	if (process->heredoc[0] != -1)
		close(process->heredoc[0]);
	if (process->heredoc[1] != -1)
		close(process->heredoc[1]);
	if (pipe(process->heredoc) == -1)
		raise_perror("heredoc buffer creation failed (pipe)", 1);
	set_signals(HEREDOC_SIG);
	heredoc_core(process, token, NULL, NULL);
	return (token);
}

void	manage_heredocs(t_processus *process)
{
	t_token	*heredoc;

	while (process)
	{
		heredoc = t_token_finding(process->tokens, HEREDOC);
		while (heredoc)
		{
			if (heredoc->token == HEREDOC)
				ft_heredoc(process, heredoc);
			heredoc = heredoc->next;
		}
		process = process->next;
	}
}
