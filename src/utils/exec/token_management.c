/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:40:48 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/02 15:26:51 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*prepare_pipes(t_token **tokens, t_envp *menvp)
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
			tmp_pipe = t_pipe_new(menvp);
		if (tmp_token->token != PIPE)
			t_token_add_back(&tmp_pipe->tokens, t_token_copy(tmp_token));
		else
		{
			t_pipe_add_back(&pipes, tmp_pipe);
			tmp_pipe = NULL;
		}
		tmp_token = tmp_token->next;
	}
	if (tmp_pipe)
		t_pipe_add_back(&pipes, tmp_pipe);
	free_t_token(*tokens);
	*tokens = NULL;
	return (pipes);
}

void	token_management(t_pipe *pipes, t_token *token, int is_sub_process)
{
	t_token	*tmp;
	int		fdin;
	int		fdout;

	fdin = -1;
	fdout = -1;
	while (token)
	{
		tmp = NULL;
		if (token->token == HERE_DOC)
			tmp = ft_here_doc(pipes, token);
		else if (token->token == REDIR_IN)
			tmp = ft_redir_in(pipes, token, &fdin);
		else if (token->token == REDIR_OUT || token->token == REDIR_APPEND_OUT)
			tmp = ft_redir_out(pipes, token, &fdout);
		token = token->next;
		if (tmp)
			t_token_del(&pipes->tokens, tmp);
	}
	if (is_sub_process)
		ft_check_redir_in_out(pipes, fdin, fdout);
	else
	{
		pipes->fds[0] = fdin;
		pipes->fds[1] = fdout;
	}
}
