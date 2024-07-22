/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:19:39 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/22 02:11:36 by tclaereb         ###   ########.fr       */
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

void	ft_exec(t_token **tokens)
{
	t_pipe	*pipes;

	pipes = prepare_pipes(tokens);
	while (pipes)
	{
		while (pipes->tokens)
		{
			printf("%s ", pipes->tokens->str);
			pipes->tokens = pipes->tokens->next;
		}
		printf("\n");
		pipes = pipes->next;
	}
}
