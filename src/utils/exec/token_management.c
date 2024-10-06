/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:40:48 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/06 18:46:22 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_processus	*prepare_processus(t_token **tokens, t_envp *menvp)
{
	t_processus	*process;
	t_processus	*tmp_pipe;
	t_token		*tmp_token;

	process = NULL;
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
			t_processus_add_back(&process, tmp_pipe);
			tmp_pipe = NULL;
		}
		tmp_token = tmp_token->next;
	}
	if (tmp_pipe)
		t_processus_add_back(&process, tmp_pipe);
	free_t_token(*tokens);
	*tokens = NULL;
	return (process);
}

void	delete_useless_tokens(t_processus *process)
{
	t_token	*tokens;
	t_token	*tmp;

	if (!process)
		return ;
	tokens = process->tokens;
	while (tokens)
	{
		if (tokens->token == REDIR_IN || tokens->token == REDIR_OUT
			|| tokens->token == REDIR_APPEND_OUT || tokens->token == HEREDOC)
		{
			tmp = tokens;
			tokens = tokens->next;
			t_token_del(&process->tokens, tmp);
			continue ;
		}
		tokens = tokens->next;
	}
}

void	token_management(t_processus *process, t_token *token,
						int is_sub_process)
{
	int		fdin;
	int		fdout;

	if (!process || ! token)
		return (raise_error("CRITICAL", "An important pointer is NULL!", 1, 1));
	fdin = -1;
	fdout = -1;
	while (token)
	{
		if (token->token == REDIR_IN)
			manage_redir_in(process, token, &fdin);
		else if (token->token == REDIR_OUT || token->token == REDIR_APPEND_OUT)
			manage_redir_out(process, token, &fdout);
		token = token->next;
	}
	if (is_sub_process)
		ft_check_redir_in_out(process, fdin, fdout);
	else
	{
		process->fds[0] = fdin;
		process->fds[1] = fdout;
	}
}
