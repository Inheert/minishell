/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:19:39 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/23 10:36:50 by tclaereb         ###   ########.fr       */
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

void	token_management(t_pipe *pipe, t_token *token)
{
	int	fd;

	if (token->token == REDIR_IN)
	{
		fd = open(token->str, O_RDONLY);
		if (fd == -1)
			return (ft_pipe_close_fds(pipe),
				raise_perror("File open failed", 1));
		if (dup2(fd, pipe->fds[0]) == -1)
			return (ft_pipe_close_fds(pipe),
				raise_perror("dup2 failed", 1));
		pipe->fds[0] = fd;
	}
	else if (token->token == REDIR_OUT)
	{
		fd = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (ft_pipe_close_fds(pipe),
					raise_perror("File open failed", 1));
		if (dup2(fd, pipe->fds[1]) == -1)
			return (ft_pipe_close_fds(pipe),
					raise_perror("dup2 failed", 1));
		pipe->fds[1] = fd;
	}
}

void	exec_main_processus(t_pipe *pipes)
{
	t_token	*tmp;

	tmp = pipes->tokens;
	while (tmp)
	{
		token_management(pipes, tmp);
		tmp = tmp->next;
	}
}

void	ft_exec(t_token **tokens)
{
	t_pipe	*pipes;

	pipes = prepare_pipes(tokens);
	if (!pipes)
		return ;
	ft_pipe_display(pipes);
	free_t_pipe(pipes);
	// if (pipe_ptr_size(pipes) == 1)
	// 	exec_main_processus(pipes);
}
