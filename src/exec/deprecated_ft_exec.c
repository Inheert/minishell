/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:34:06 by Théo              #+#    #+#             */
/*   Updated: 2024/07/12 04:04:51 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_ftdin(t_token *token)
{
	int	fd;

	fd = -1;
	while (token)
	{
		if (token->token == REDIR_IN)
		{
			if (fd != -1)
				close(fd);
			fd = open(token->str, O_RDONLY);
			if (fd == -1)
				return (raise_perror(token->str, 0), -1);
		}
		token = token->next;
	}
	return (fd);
}

int	get_ftdout(t_token *token)
{
	int	fd;

	fd = -1;
	while (token)
	{
		if (token->token == REDIR_OUT)
		{
			if (fd != -1)
				close(fd);
			fd = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (raise_perror(token->str, 0), -1);
		}
		token = token->next;
	}
	return (fd);
}

t_pipe	*prepare_pipes(t_token *token)
{
	t_pipe			*pipe;
	t_pipe			*tmp_pipe;
	t_token			*tmp_token;
	t_token			*pipe_token;
	unsigned int	n;

	pipe = NULL;
	tmp_token = token;
	n = 0;
	while (token)
	{
		if (token->token == PIPE)
		{
			if (token->prev)
				token->prev->next = NULL;
			token->prev = NULL;
			tmp_pipe = ft_pipe_new(tmp_token);
			if (!tmp_pipe)
				return (free_t_pipe(pipe), NULL);
			ft_pipe_add_back(&pipe, tmp_pipe);
			tmp_token = token->next;
			pipe_token = token;
			token = token->next;
			if (pipe_token->next)
				pipe_token->next->prev = NULL;
			free_t_token(pipe_token);
			n = 0;
		}
		else
			token = token->next;
		n++;
	}

	pipe = ft_pipe_new(token);
	return (pipe);
}

int	execute_commands(t_token *token)
{
	int		fds[2];
	t_token	*token_tmp;
	t_pipe	*pipe;

	pipe = prepare_pipes(token);
	free_t_pipe(pipe);
	token_tmp = token;
	token = (t_token *)token_tmp;
	fds[0] = get_ftdin(token);
	if (fds[0] == -1)
		return (errno);
	fds[1] = get_ftdout(token);
	if (fds[1] == -1)
		return (close(fds[0]), errno);
	printf("fdin: %d\n", fds[0]);
	printf("fdout: %d\n", fds[1]);
	close(fds[0]);
	close(fds[1]);
	return (0);
}
