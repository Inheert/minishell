/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:40:48 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/05 18:24:53 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_processus	*prepare_processus(t_token **tokens, t_envp *menvp)
{
	t_processus	*pipes;
	t_processus	*tmp_pipe;
	t_token		*tmp_token;

	pipes = NULL;
	tmp_pipe = NULL;
	tmp_token = *tokens;
	while (tmp_token)
	{
		if (!tmp_pipe)
			tmp_pipe = t_processus_new(menvp);
		if (tmp_token->token != PIPE)
			t_token_add_back(&tmp_pipe->tokens, t_token_copy(tmp_token));
		else
		{
			t_processus_add_back(&pipes, tmp_pipe);
			tmp_pipe = NULL;
		}
		tmp_token = tmp_token->next;
	}
	if (tmp_pipe)
		t_processus_add_back(&pipes, tmp_pipe);
	free_t_token(*tokens);
	*tokens = NULL;
	return (pipes);
}

void	token_management(t_processus *pipes, t_token *token, int is_sub_process)
{
	int		fdin;
	int		fdout;

	fdin = -1;
	fdout = -1;
	while (token)
	{
		if (token->token == REDIR_IN)
			ft_redir_in(pipes, token, &fdin);
		else if (token->token == REDIR_OUT || token->token == REDIR_APPEND_OUT)
			ft_redir_out(pipes, token, &fdout);
		token = token->next;
	}
	if (is_sub_process)
		ft_check_redir_in_out(pipes, fdin, fdout);
	else
	{
		pipes->fds[0] = fdin;
		pipes->fds[1] = fdout;
	}
}
