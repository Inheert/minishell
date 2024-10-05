/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:55:15 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/21 23:55:15 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_ptr(char **ptr)
{
	size_t	i;
	size_t	size;

	if (!ptr || !*ptr)
		return ;
	i = -1;
	size = str_ptr_size(ptr);
	while (++i < size && ptr[i])
		ft_free(ptr[i]);
	ft_free(ptr);
}

void	free_one_t_token(t_token *token)
{
	if (!token)
		return ;
	if (token->str)
		ft_free(token->str);
	ft_free(token);
}

void	free_t_token(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token)
	{
		tmp = token->next;
		free_one_t_token(token);
		token = tmp;
	}
}

void	free_t_processus(t_processus *pipe)
{
	t_processus	*tmp;

	if (!pipe)
		return ;
	while (pipe)
	{
		free_t_token(pipe->tokens);
		tmp = pipe;
		pipe = pipe->next;
		ft_free(tmp);
	}
}

void	free_t_envp(t_envp *menvp)
{
	ft_free(menvp->name);
	if (menvp->value)
		ft_free(menvp->value);
	ft_free(menvp);
}
