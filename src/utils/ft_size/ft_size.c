/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:55:29 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/21 23:55:29 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	t_token_count_specific(t_token *token, t_token_type code)
{
	unsigned int	size;

	if (!token)
		return (0);
	size = 0;
	while (token)
	{
		if (token->token == code)
			size++;
		token = token->next;
	}
	return (size);
}

unsigned int	t_token_size(t_token *token)
{
	unsigned int	size;

	if (!token)
		return (0);
	size = 0;
	while (token)
	{
		token = token->next;
		size++;
	}
	return (size);
}

unsigned int	t_processus_size(t_processus *pipe)
{
	unsigned int	size;

	if (!pipe)
		return (0);
	size = 0;
	while (pipe)
	{
		pipe = pipe->next;
		size++;
	}
	return (size);
}

unsigned int	t_envp_size(t_envp *menvp)
{
	unsigned int	size;

	if (!menvp)
		return (0);
	size = 0;
	while (menvp)
	{
		menvp = menvp->next;
		size++;
	}
	return (size);
}

unsigned int	str_ptr_size(char **ptr)
{
	unsigned int	size;

	if (!ptr || !*ptr)
		return (0);
	size = 0;
	while (ptr[size])
		size++;
	return (size);
}
