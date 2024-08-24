/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:40:48 by tclaereb          #+#    #+#             */
/*   Updated: 2024/08/24 16:41:11 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*prepare_pipes(t_token **tokens)
{
	t_pipe	*pipes;
	t_pipe	*tmp_pipe;
	t_token	*tmp_token;

	pipes = NULL;
	tmp_pipe = NULL;
	tmp_token = *tokens;
	while (tmp_token)
	{
		if (!tmp_pipe)
			tmp_pipe = ft_pipe_new();
		if (tmp_token->token != PIPE)
			ft_token_add_back(&tmp_pipe->tokens, ft_token_copy(tmp_token));
		else
		{
			ft_pipe_add_back(&pipes, tmp_pipe);
			tmp_pipe = NULL;
		}
		tmp_token = tmp_token->next;
	}
	if (tmp_pipe)
		ft_pipe_add_back(&pipes, tmp_pipe);
	free_t_token(*tokens);
	*tokens = NULL;
	return (pipes);
}

void	token_management(t_pipe *pipes, t_token *token)
{
	t_token	*tmp;
	char	*buff;
	int		fdin;
	int		fdout;

	fdin = -1;
	fdout = -1;
	while (token)
	{
		tmp = NULL;
		buff = NULL;
		if (token->token == HERE_DOC)
		{
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
				return (ft_pipe_close_fds(pipes), raise_perror("dup2 failed", 1));
			tmp = token;
		}
		else if (token->token == REDIR_IN)
		{
			fdin = open(token->str, O_RDONLY);
			if (fdin == -1)
				return (ft_pipe_close_fds(pipes),
					raise_perror(token->str, 1));
			tmp = token;
		}
		else if (token->token == REDIR_OUT)
		{
			fdout = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fdout == -1)
				return (ft_pipe_close_fds(pipes),
					raise_perror(token->str, 1));
			tmp = token;
		}
		token = token->next;
		ft_token_del(&pipes->tokens, tmp);
	}
	if (fdin != -1)
	{
		if (dup2(fdin, 0) == -1)
			return (ft_pipe_close_fds(pipes),
					raise_perror("dup2 failed", 1));
		pipes->fds[0] = fdin;
	}
	if (fdout != -1)
	{
		if (dup2(fdout, 1) == -1)
			return (ft_pipe_close_fds(pipes),
					raise_perror("dup2 failed", 1));
		pipes->fds[1] = fdout;
	}
}
